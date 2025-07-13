# OpenCAN

## 🔍 Project Overview

OpenCAN is a microcontroller-based project that reads live OBD-II data (e.g., engine RPM) via Bluetooth and drives an analog pointer using a stepper motor. In a world where dashboards are becoming increasingly digital, OpenCAN revives the tactile, satisfying experience of real analog movement—because sometimes, a physical needle sweeping across a dial just feels more alive than pixels on a screen. The goal is to create smooth and responsive pointer movement despite delays in OBD-II data retrieval.

---

## 🧰 Hardware Components

### Core Modules

* 1x [ESP32-DEVKIT-V1](https://de.aliexpress.com/item/1005006128432036.html?spm=a2g0o.productlist.main.1.36c150d9Vynner&algo_pvid=f1c66e43-4416-4eb8-ad0a-b9c25d05ed2b&algo_exp_id=f1c66e43-4416-4eb8-ad0a-b9c25d05ed2b-0&pdp_ext_f=%7B%22order%22%3A%22461%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%212.14%211.75%21%21%2117.55%2114.36%21%40210385bb17523962162358814e4418%2112000046958263336%21sea%21DE%216233624885%21X&curPageLogUid=PHptQbbetuGY&utparam-url=scene%3Asearch%7Cquery_from%3A) (30-Pin)
* 1x X27168 Stepper Motor

### Power Supply

* 1x CN3903 Buck Converter (12V to 5V)
* 1x TVS Diode (1N6280A)
* 1x 470nF 16V Capacitor
* 1x Fuse Holder with 200mA Glass Fuse

### Additional Components

* 2x 15-Pin Header Socket
* 1x 2-Pin Screw Terminal
* 3x M3 Screws
* 1x [Custom OpenCAN PCB](#-pcb-layout)

---

## 🔌 Schematic

![Schematic](assets/schematic.png)

---

## 🧾 PCB Layout

![PCB Design](assets/pcb_design.png)

---

## ⚡ Electrical Flow Diagram

```text
12V (Car Battery)
├── TVS Diode
├── LED (optional)
├── Buck Converter (12V → 5V)
│   ├── Fuse (200mA)
│   ├── Capacitor (470nF)
│   └── ESP32
│       ├── Buzzer
│       └── Stepper Motor (X27168)
```

---

## 🔁 Pointer Movement Logic (Interpolation Algorithm)

### ⚠️ The Problem

OBD-II data via Bluetooth (e.g., ELM327) introduces blocking delays (typically 80–150 ms). During this blocking time, the microcontroller can't update the motor, resulting in jerky and unresponsive pointer behavior.

### 💡 The Solution: Linear Interpolation

To solve this, OpenCAN simulates smooth transitions between OBD data points using linear interpolation:

#### 1. Periodic, Blocking Data Fetch

* A new target value is fetched every `obdRequestInterval` (e.g., 150ms)
* When new data arrives:

  * Start point (`V0`) is set to the previous target value
  * End point (`V1`) is the newly received value
  * Start time (`t0`) is recorded

#### 2. Continuous Interpolation in Loop

* On every iteration of the `loop()`, if not blocked by data fetch:

  * Calculate progress:

    ```
    progress = (currentTime - t0) / obdRequestInterval
    ```
  * Calculate interpolated target:

    ```
    V_interpolated = V0 + (V1 - V0) * progress
    ```
  * Send `V_interpolated` to `motor.setTargetAngle()`
  * `motor.update()` ensures the motor continuously moves towards this value

### ✅ Result

* The pointer moves smoothly between data points
* Movement appears fluid and responsive, independent of the actual data delay

---

## 🧠 Future Improvements (optional)

* Support for multiple gauges
* Add OLED/LCD display for digital readouts
* Log OBD data to SD card
* Wi-Fi OTA updates
