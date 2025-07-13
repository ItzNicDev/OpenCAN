# OpenCAN

## 🔍 Project Overview

OpenCAN is a microcontroller-based project that reads live OBD-II data (e.g., turbo boost or engine rpm) via Bluetooth and drives an analog pointer using a stepper motor. In a world where dashboards are becoming increasingly digital, OpenCAN revives the tactile, satisfying experience of real analog movement—because sometimes, a physical needle sweeping across a dial just feels more alive than pixels on a screen. The goal is to create smooth and responsive pointer movement despite delays in OBD-II data retrieval.

---

## 🧰 Hardware Components

### Core Modules

* 1x [ESP32-DEVKIT-V1](https://de.aliexpress.com/item/1005006128432036.html?spm=a2g0o.productlist.main.1.36c150d9Vynner&algo_pvid=f1c66e43-4416-4eb8-ad0a-b9c25d05ed2b&algo_exp_id=f1c66e43-4416-4eb8-ad0a-b9c25d05ed2b-0&pdp_ext_f=%7B%22order%22%3A%22461%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%212.14%211.75%21%21%2117.55%2114.36%21%40210385bb17523962162358814e4418%2112000046958263336%21sea%21DE%216233624885%21X&curPageLogUid=PHptQbbetuGY&utparam-url=scene%3Asearch%7Cquery_from%3A) (30-Pin)
* 1x [X27168 Stepper Motor](https://de.aliexpress.com/item/1005001661473145.html?spm=a2g0o.productlist.main.1.5b1e7249E1hdXX&algo_pvid=ca190c73-cd1b-4d43-8954-def95e9eff1c&algo_exp_id=ca190c73-cd1b-4d43-8954-def95e9eff1c-0&pdp_ext_f=%7B%22order%22%3A%227%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%212.32%211.49%21%21%212.65%211.70%21%402103849717523962718252836e21f9%2112000017032540183%21sea%21DE%216233624885%21X&curPageLogUid=fd8ccaZ4X9Gl&utparam-url=scene%3Asearch%7Cquery_from%3A)

### Power Supply

* 1x [CN3903 Buck Converter](https://de.aliexpress.com/item/1005003239596512.html?spm=a2g0o.productlist.main.2.1176599feL7O6y&algo_pvid=c9ccdcb8-a0d6-4b6f-8f0f-f2d4d9f27fd4&algo_exp_id=c9ccdcb8-a0d6-4b6f-8f0f-f2d4d9f27fd4-1&pdp_ext_f=%7B%22order%22%3A%2239%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%210.45%210.45%21%21%213.67%213.67%21%402103868817523963088208918ec918%2112000024801303076%21sea%21DE%216233624885%21X&curPageLogUid=ReUqz2F9l8rW&utparam-url=scene%3Asearch%7Cquery_from%3A) (12V to 5V)
* 1x [TVS Diode](https://www.amazon.com/dp/B079KHXZHK?psc=1&ref_=cm_sw_r_cp_ud_ct_7PG0FPYTPC88BNJHQAFG_1) (1N6280A)
* 1x [470nF 16V Capacitor](https://de.aliexpress.com/item/1005006075263546.html?spm=a2g0o.productlist.main.23.75b0c9c33Nwfwx&algo_pvid=88c34e0a-e5f4-4e8d-ad2e-4e08d97886e0&algo_exp_id=88c34e0a-e5f4-4e8d-ad2e-4e08d97886e0-20&pdp_ext_f=%7B%22order%22%3A%2214%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%211.25%211.15%21%21%211.42%211.31%21%40211b6c1917523964976586004e47b6%2112000035613539186%21sea%21DE%216233624885%21X&curPageLogUid=O8hK2Kwejpsj&utparam-url=scene%3Asearch%7Cquery_from%3A)
* 1x [Fuse Holder](https://www.amazon.com/-/de/dp/B074N1NMMX?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=2SBTZKT3UCUQ&dib=eyJ2IjoiMSJ9.nHToP20kJLmZshZ_M0ktCMHD9RnAVLlrLyILkyOg4lknW3CdUnjPFvPezVrIsojj-x5a5LbH_jVb_DVyeVXdUkSCjx9jykRxEJOJs6KnH9VgOINRdQscJS-2rSCpN-LD_lS8hbSwVszTsF0Q66Tp0WjJC0yIHGaB9o4uE6svlwgQr0cxuMLgJ_0RaKG_0Viw.0sutghmPgI0P8xBa6hq1SZ7FRD4MUOUzfyrJNIjGa4g&dib_tag=se&keywords=sicherungshalter+pcb&qid=1752396826&sprefix=sicherungshalter+pc%2Caps%2C221&sr=8-30&xpid=1sYgBZV_GLwhn) with [200mA Glass Fuse](https://www.amazon.com/-/de/dp/B074L7Z342?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=13Z6DV9I4ZBOU&dib=eyJ2IjoiMSJ9.LIM3b-PhLp5Zu3U4-TNOuEpsv8Xwz1ZNONAtzY1JwJ57WUKEqeybomcOKXZifb_w91XlQu3fEkOsbyxH2hhwrGBx3Tjdw4O55JKQHAp-My_aW8m_vvN66nC-p8kEwng9VIYlZ-A5hHB-413iY5QFCsBTvZoy2Px10v3INejbJEgXiGtwYZWc_V79y10wjGft_u7EylvF7QK2PQ6ovFoYmjSz5XYwrjMQoylsFJFRfkK3eteB7VwcgbsNa3oiJXc_iVU15HVRm8ROSzFozChDlb8WGJkCRdJcjQ-zGeCRoqM.VSXbczhZPxHbQfqDxj-wtgajRLVUzfQy67ioxIvlZ60&dib_tag=se&keywords=glass+fuse+200ma&qid=1752396753&sprefix=glass+fuse+200m%2Caps%2C245&sr=8-5)

### Additional Components

* 2x [15-Pin Header Socket](https://www.amazon.com/-/de/dp/B08DVGCTKT?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=GXC2RSEQUWJJ&dib=eyJ2IjoiMSJ9.F6JUkZTU-stCHqmq-iAIuMEe415-CNFjACNxmpJpwnnrd2NBhMQtE_Y7NULHezwmB6dUmVihC-APueO34gEUiBNyaJpRZ15_bW7hyfXwGCfdxfdZ9eg9GHqSc0hVUuWBBmPzoyE5DJ0V1HI3yE12K4terh7mSPem8wkGEgW4XKGmdQmycc5AUeHSOS2spECj4DL_K3xhjk8wHer8fFmYJRZf6kflPKP6-pJJSFBI0iQ.WnPQ1nI-MXgR_V82nt2K_3ra2xhozqH3QIGRJM6YfT8&dib_tag=se&keywords=pin+header&qid=1752396878&sprefix=pin+header%2Caps%2C221&sr=8-11)
* 1x [2-Pin Screw Terminal](https://www.amazon.com/-/de/dp/B07QRHJ489?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dib=eyJ2IjoiMSJ9.uJUPY1QHu_fWzphlgpV5C9rjg_-6kPf9AhSlQLb9Lxgu2EzChWYjN7tAZ6Jf-WzKX6FF6YZppyRDppM2nW7oNz7bXXqc-LfImijAoRrFTN8MkNsacd6QBKhOIWn6UlQmwgnNxaHL3NZc-QQOLkMQ-nxxzz4H-Z1QKORLQTGsf65v5CTFbj2D6kPghJDnSBpAYk3Nm0HYQcfwZZjqPUVJ4k--A6OCZ4J9Wg6OBk0eQ10.crXagmvjyYh5XPkeH17DnOu5PxqpbA1QkpEDMX9H0zw&dib_tag=se&keywords=2-Pin%2BScrew%2BTerminal&qid=1752396909&sr=8-3&th=1)
* 3x [M3 Screws](https://de.aliexpress.com/item/1005004527586307.html?spm=a2g0o.productlist.main.7.1c0e83pH83pHDK&algo_pvid=ee12877b-5e38-4728-beaa-28559f366fc3&algo_exp_id=ee12877b-5e38-4728-beaa-28559f366fc3-6&pdp_ext_f=%7B%22order%22%3A%226115%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%210.96%210.96%21%21%211.09%211.09%21%40210385bb17523969573361899e441d%2112000029486656871%21sea%21DE%216233624885%21X&curPageLogUid=n5f3XXGpyUBB&utparam-url=scene%3Asearch%7Cquery_from%3A)
* 3x [M3 Threaded heat-set inserts](https://de.aliexpress.com/item/1005006472962973.html?spm=a2g0o.productlist.main.1.687c5125OYvhMS&algo_pvid=aa5009d6-1880-4990-88e9-70ea73f17982&algo_exp_id=aa5009d6-1880-4990-88e9-70ea73f17982-0&pdp_ext_f=%7B%22order%22%3A%226242%22%2C%22eval%22%3A%221%22%7D&pdp_npi=4%40dis%21EUR%214.78%211.75%21%21%215.45%211.99%21%40210391a017523970797643092e154c%2112000037324316041%21sea%21DE%216233624885%21X&curPageLogUid=hB6lhYICHs4k&utparam-url=scene%3Asearch%7Cquery_from%3A)
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
