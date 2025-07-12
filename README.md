# OpenCAN

## Parts List
- 1x ESP32-DEVKIT-V1 30-Pin
- 2x Header Socket (15 pins each)
- 1x Screw Terminal (2 pin)
- 1x TVS Diode (1N6280A)
- 1x CN3903 Buck Converter
- 1x Fuse Holder (glass fuse)
- 1x Glass Fuse (200mA)
- 1x 470nF 16V Capacitor
- 3x M3 Screw
- 1x OpenCAN custom PCB

## Electric Flows

```bash
├── 12V (Car Battery)
│   ├── TVS Diode
│   ├── LED
│   ├── Buck Converter (12V to 5V)
│       ├── Fuse (200mA)
│       ├── Capacitor (470nF 16V)
│       └── ESP32
│           ├── Buzzer
│           └── X27168
```

## Bluetooth-Kommunikations-Ablauf:
```
> AT
> AT+RESET
> AT+VERSION?

> AT+ROLE=1
> AT+BIND=<NAP:UAP:LAP>
> AT+PSWD=<PASSWORD>
```
