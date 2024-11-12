# OpenCAN

## Part List
- 1x ESP32/Arduino Uno/Arduino Nano
- 3x X27 168 Stepper Motor [Amazon Link](https://shorturl.at/sV0GF)
- 1x AX1201728SG Driver-IC [Amazon Link](https://shorturl.at/P5nwd)
- 1x SOP28 zu DIP28 Adapter [Amazon Link](https://shorturl.at/ZedPl)

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
