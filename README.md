# 🛠️ Line Follower Robot with PID Control using QTR Sensor Array

This is an Arduino-based line follower robot that uses an 8-sensor QTR-8A IR array and the SparkFun TB6612FNG motor driver. The bot features smooth and responsive movement using a PID control algorithm and supports calibration, gradual startup, and speed regulation.

---

## 📦 Components Used

- Arduino Uno/Nano
- QTR-8A Reflectance Sensor Array
- TB6612FNG Motor Driver
- 2 DC N20 Geared Motors
- 2 Push Buttons (Start and Calibrate)
- Chassis with wheels and Castor Wheel
- 12V or 9V Li-Po battery pack

---

## 🔌 Pin Configuration

| Component         | Arduino Pin |
|------------------|-------------|
| QTR Sensor Pins   | A0–A7       |
| QTR LED Pin       | D2          |
| Motor A (AIN1/2)  | D3 / D4     |
| Motor B (BIN1/2)  | D7 / D8     |
| Motor PWM A/B     | D5 / D6     |
| Standby (STBY)    | D9          |
| Calibrate Button  | D11         |
| Start Button      | D10         |
| Built-in LED      | LED_BUILTIN |

---

## 🔧 Libraries Required

- [QTRSensors](https://github.com/pololu/qtr-sensors-arduino)
- [SparkFun TB6612FNG Motor Driver](https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library)

Install both libraries via the Arduino Library Manager or from their GitHub pages.

---

## ⚙️ How It Works

1. **Calibration Phase:**
   - Press the calibration button before starting.
   - The robot calibrates the sensors to the line surface for 10 seconds.

2. **Start Phase:**
   - Press the start button to begin line following.
   - The robot ramps up, then follows the line using a PID controller.

3. **PID Control:**
   - `Kp`, `Ki`, and `Kd` values adjust how the robot corrects its path based on error from the center.
   - The correction adjusts left/right motor speeds to stay centered on the line.
