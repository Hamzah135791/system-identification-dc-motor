# DC Motor System Identification via Least Squares Estimation (LSE)

An end-to-end data-driven system identification framework to model the dynamic response of a JGA25 DC Motor. The project utilizes a Pseudo-Random Binary Sequence (PRBS) excitation signal generated via Arduino to persistently excite system dynamic modes, followed by parameter estimation using an Auto-Regressive with Exogenous Input (ARX) model solved via Ordinary Least Squares (LSE) in Python.

---

## 🛠️ Hardware Specifications & Pin Mapping

### Components Used
* **Microcontroller:** Arduino Uno
* **Motor Driver:** L298N Dual H-Bridge Motor Driver
* **Actuator:** JGA25 DC Motor (Powered by External DC Power Supply)
* **Sensor:** JGA25 Integrated Hall-Effect Quadrature Encoder
* **Data Interface:** USB Serial Communication (115200 baud)

### Pin Connections

| Component | Pin | Description |
| :--- | :--- | :--- |
| **L298N ENA (PWM)** | Digital Pin `9` | Motor speed control via PWM signal |
| **L298N IN1** | Digital Pin `7` | Direction control terminal 1 |
| **L298N IN2** | Digital Pin `8` | Direction control terminal 2 |
| **Encoder Channel A** | Digital Pin `2` | Hardware Interrupt 0 for RPM calculations |
| **External Power Supply** | L298N Power Terminals | External DC voltage supply for motor drive |

---

## 💻 Software & Dependencies

### Firmware (Arduino IDE)
* **Built-in Libraries:** `Arduino.h` (Hardware Interrupts & PWM)

### Analysis Script (Python 3.x)
Ensure you have the required Python packages installed:

```bash
pip install numpy pandas matplotlib
