# OpenCAN


Android App:
(Serial Bluetooth Terminal)[https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=de]


## Part List
- 1x ESP32/Arduino Uno/Arduino Nano
- 3x X27 168 Stepper Motor [Amazon Link](https://shorturl.at/sV0GF)
- 1x AX1201728SG Driver-IC [Amazon Link](https://shorturl.at/ZedPl)
- 1x SOP28 zu DIP28 Adapter

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
