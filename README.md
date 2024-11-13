# OpenCAN

## Part List
- 1x ESP32/Arduino Uno/Arduino Nano
- 1x OBDII Bluetooth Adapter [Amazon Link](https://shorturl.at/WAysj) [AliExpress](https://shorturl.at/v9x02)
- 3x X27 168 Stepper Motor [Amazon Link](https://shorturl.at/sV0GF) [AliExpress](https://shorturl.at/FqCGk)
- 1x AX1201728SG Driver-IC [Amazon Link](https://shorturl.at/P5nwd) [AliExpress](https://shorturl.at/m2FAD)
- 1x SOP28 zu DIP28 Adapter [Amazon Link](https://shorturl.at/ZedPl) [AliExpress](https://shorturl.at/1MLg4)

## Anleitungen
- [Stepper Motor Anleitung für Treiber](https://guy.carpenter.id.au/gaugette/2017/04/29/switecx25-quad-driver-tests/)

## Diagramme
![Verkabelung X27 168 mit AX1201728SG](https://shorturl.at/Gp5xT)

## Bluetooth-Kommunikations-Ablauf:
```
> AT
> AT+RESET
> AT+VERSION?

> AT+ROLE=1
> AT+BIND=<NAP:UAP:LAP>
> AT+PSWD=<PASSWORD>
```
