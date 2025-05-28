
# OpenCAN ![logo](./assets/logo.svg)
### Pointer Movement Logic (Interpolation Algorithm)

The core challenge in controlling the pointer was the slow and blocking nature of OBD-II data queries. To ensure a smooth and responsive pointer movement, an interpolation algorithm has been implemented.

**Problem:** OBD-II queries via Bluetooth (ELM327) can block the microcontroller for a significant duration (e.g., 80-150ms). During this blockage, the motor cannot be updated, leading to jerky motion and preventing the pointer from reacting quickly to sudden data changes.

**Solution (Linear Interpolation):**
The algorithm addresses this by **simulating** the pointer's movement between the "actual" OBD data points. It does this by continuously calculating intermediate target values and sending them to the motor.

1.  **Periodic, Blocking Data Fetch:** At a fixed interval, defined by `obdRequestInterval` (e.g., 150ms), a new, smoothed target value is retrieved from the OBD adapter. This step temporarily blocks the microcontroller. When a new value is successfully obtained:
    * The **Start Point** for interpolation, $V_0$ (`lastObdTargetDegree`), is set to the value the pointer was aiming for at the beginning of the current interval.
    * The **End Point** for interpolation, $V_1$ (`nextObdTargetDegree`), is set to the newly received and smoothed target value.
    * The timestamp of this update, $t_0$, is recorded (`lastObdRequestTime`).

2.  **Continuous Interpolation:** In every `loop()` iteration where the microcontroller *not* blocked by the OBD query, the algorithm calculates an **intermediate target value** ($V_{interpolated}$). This calculation ensures the pointer moves smoothly from $V_0$ to $V_1$ over the duration of the `obdRequestInterval`.

    Let $t_{current}$ be the current timestamp within the `loop()` iteration.
    The **progress** through the current interpolation interval is calculated as:
    
    $$\text{progress} = \frac{t_{current} - t_0}{\text{obdRequestInterval}}$$
    This $\text{progress}$ value ranges from 0 (at the start of the interval, $t_{current} = t_0$) to 1 (at the expected end of the interval, $t_{current} = t_0 + \text{obdRequestInterval}$).

    The **interpolated target value** ($V_{interpolated}$) is then calculated using the formula for linear interpolation:
    $$V_{interpolated} = V_0 + (V_1 - V_0) \times \text{progress}$$

4.  **Smooth Motor Control:** This continuously calculated $V_{interpolated}$ is immediately passed to the `motor.setTargetAngle()` method. The `motor.update()` method, which runs in every `loop()` iteration, then moves the pointer smoothly and fluidly towards this constantly updating intermediate target.

**Result:** The pointer glides evenly from one target to the next, even if the underlying OBD data points are abrupt and retrieved slowly. The movement is no longer solely tied to the latency of the OBD communication but appears fluid and responsive by filling the gaps between actual data points.
