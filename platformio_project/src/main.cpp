#include "Arduino.h"
#include "ObdUtils.h"
#include "X27168Driver.h"
#include "MappingUtils.h"
#include "ELM327Driver.h"

MappingUtils mappingUtils;
X27168Driver motor(945, 14, 16, 17, 18);
uint8_t obdAddress[] = {0x00, 0x1D, 0xA5, 0x07, 0x52, 0x39};
ELM327Driver elm327(obdAddress);

// Zeitsteuerung für OBD-Abfragen
unsigned long lastObdRequestTime = 0;
// WICHTIG: Setze diesen Wert auf die MAXIMALE Dauer, die elm327.getResponse() blockieren kann
// plus einen kleinen Puffer. Miss das genau aus!
const unsigned long obdRequestInterval = 80; // Beispiel: Wenn getResponse bis zu 120ms dauert, nimm 150ms.

// Für die Glättung der OBD-Werte
float rawDegree = 0; // Der letzte ROH-Winkel von OBD (muss global sein)
float smoothedDegree = mappingUtils.boostToDegree(0);
const float smoothingFactor = 0.65; // Dein Glättungsfaktor

// Für die Interpolation
float lastObdTargetDegree = mappingUtils.boostToDegree(0); // Das ZIEL, das beim LETZTEN OBD-Update gesetzt wurde
float nextObdTargetDegree = mappingUtils.boostToDegree(0); // Das ZIEL, das beim NÄCHSTEN OBD-Update erreicht werden soll

void setup() {
  Serial.begin(115200);
  Serial.println("System Start...");
    motor.reference();


  elm327.setupBluetoothComunication();
  Serial.println("Bluetooth setup complete.");

  motor.reference();
  Serial.println("Motor referenced.");

  delay(1000);

  // Setze die initialen Ziele auf den Leerlaufwert
  rawDegree = mappingUtils.boostToDegree(0);
  smoothedDegree = rawDegree;
  lastObdTargetDegree = rawDegree;
  nextObdTargetDegree = rawDegree;

  motor.setTargetAngle(smoothedDegree); // Setze das erste Ziel für den Motor
}

void loop()
{
  // Teil 1: OBD-Daten alle 'obdRequestInterval' Millisekunden abrufen (BLOCKIEREND)
  // Wenn es Zeit für ein neues OBD-Update ist:
  if (millis() - lastObdRequestTime >= obdRequestInterval)
  {
    lastObdRequestTime = millis(); // Zeitpunkt der letzten Abfrage aktualisieren

    // DEBUG: Messen, wie lange die OBD-Abfrage dauert
    unsigned long obdStartTime = micros();
    float boost = elm327.getResponse(ObdSensorType::Boost); // <-- Hier blockiert es!
    unsigned long obdEndTime = micros();
    Serial.print("OBD response time: ");
    Serial.print((obdEndTime - obdStartTime) / 1000.0); // In Millisekunden
    Serial.println(" ms");

    // Speichere den zuletzt gelesenen Rohwert und das vorherige Ziel
    // Diese Werte werden für die Interpolation im nächsten Intervall benötigt
    lastObdTargetDegree = nextObdTargetDegree; // Das bisherige "Next-Ziel" wird zum "Last-Ziel"
    
    rawDegree = mappingUtils.boostToDegree(boost); // Hole den NEUEN Roh-Winkel

    // Wende Glättung auf den NEUEN OBD-Wert an, um das NÄCHSTE ZIEL zu bestimmen
    smoothedDegree = (rawDegree * smoothingFactor) + (smoothedDegree * (1.0 - smoothingFactor));
    nextObdTargetDegree = smoothedDegree; // Das ist das tatsächliche ZIEL, das der Motor in 'obdRequestInterval' erreichen soll

    // Optional: Für Debugging, den Sprung in den Zielen verfolgen
    // Serial.print("New OBD Target: ");
    // Serial.println(nextObdTargetDegree);
  }

  // Teil 2: Interpolation des Zielwerts (immer nicht-blockierend!)
  // Berechne einen Zwischenwert, der den Zeiger flüssig zum nextObdTargetDegree bewegt.
  // Das passiert in JEDEM loop()-Durchlauf.

  float interpolatedDegree;
  unsigned long timeElapsed = millis() - lastObdRequestTime; // Zeit seit der letzten OBD-Abfrage

  // Wenn die Zeit abgelaufen ist oder noch kein Intervall gestartet, bleibe beim letzten Ziel
  if (timeElapsed >= obdRequestInterval) {
      interpolatedDegree = nextObdTargetDegree; // Sollte hier eigentlich nicht passieren, da der if-Block greift
  } else {
      // Berechne den Fortschritt als Verhältnis der Zeit zum Gesamtintervall
      float progress = (float)timeElapsed / obdRequestInterval;
      
      // Lineare Interpolation zwischen lastObdTargetDegree und nextObdTargetDegree
      interpolatedDegree = lastObdTargetDegree + (nextObdTargetDegree - lastObdTargetDegree) * progress;
  }
  
  // Setze das interpolierte Ziel für den Motor
  motor.setTargetAngle(interpolatedDegree);

  // Teil 3: Motor in jedem loop()-Durchlauf aktualisieren (NICHT blockierend)
  // Das ist ABSOLUT ENTSCHEIDEND für die Motorbewegung!
  motor.update();

  // KEIN delay() HIER! Ein delay() würde motor.update() massiv ausbremsen.
}