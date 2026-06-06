# 4WD Arduino Robot Car
[🚀 View Interactive Schematic Dashboard](https://tanixshivram.github.io/Arduino-Robo-Car/)

## Overview
A dual-mode autonomous and Bluetooth-controlled 4WD robot platform. 

## Technical Design & Safety
* **Logic Level Shifting:** Implemented a voltage divider (1kΩ/2kΩ) to protect the 3.3V HC-05 RX pin from 5V Arduino signals.
* **Safety Override:** Integrated an HC-SR04 ultrasonic sensor that acts as an interrupt-level safety layer, overriding manual Bluetooth commands if an obstacle is detected within 20cm.
* **Control Logic:** Utilizes the "Arduino Bluetooth Control" app for serial-to-Bluetooth bridge communication.
* **Electrical Integrity:** Common grounding across the L298N driver, Arduino, and Bluetooth module ensures signal stability and noise reduction.

## Project Demo
*(Coming Soon: Demo video of autonomous braking and Bluetooth control)*
