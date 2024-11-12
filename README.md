# OpenCAN


Android App:
(Serial Bluetooth Terminal)[https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=de]


## Material List
- ESP32/Arduino Uno/Arduino Nano
- X27 168 Stepper Motor
- AX1201728SG Driver-IC

[Stepper Motor Anleitung für Treiber](https://guy.carpenter.id.au/gaugette/2017/04/29/switecx25-quad-driver-tests/)

## Bluetooth-Kommunikations-Ablauf:
```
> AT
> AT+RESET
> AT+VERSION?

> AT+ROLE=1
> AT+BIND=<NAP:UAP:LAP>
> AT+PSWD=<PASSWORD>
```
