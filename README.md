# 🏆 Line Follower Robot (RoboCup MICA 2025 Winner)

This repository contains the firmware and design details for the high-speed autonomous line-following robot that secured **1st Place** at the RoboCup MICA Egypt 2025 competition.

## 🥇 Achievement Highlight
* **Ranking:** Secured **1st Place** out of **134 competing teams**.
* **Role:** **Team Leader** – Responsible for system architecture, firmware development, and team coordination.

## 🚀 The Challenge: Innovation under Constraints
During the competition, a specific technical constraint was imposed: **The use of standard PID libraries or algorithms was restricted.** To overcome this, I led my team to develop a custom, high-speed navigation logic using **Optimized Nested Conditionals (If/While loops)**. This allowed our robot to achieve high-performance steering and stability, outperforming 133 other designs.

## 🧠 Key Features & Algorithms

### 1. Custom Steering Logic
* **Precision Sensing:** Utilizes a 5-IR reflectance sensor array to detect line position with high granularity.
* **Optimized Logic:** Replaced PID with a fine-tuned state machine that handles straight paths and sharp turns with minimal oscillation.

### 2. Advanced Self-Recovery Mechanism (Back-tracking)
To ensure the robot's robustness during the race and avoid disqualification, I implemented a **Self-Correction Algorithm**:
* **Error Detection:** The robot monitors the time elapsed since the last line detection.
* **Auto-Recovery:** If the robot loses the track, it automatically triggers a **Reverse-Search mode**.
* **Back-tracking:** The robot moves backward intelligently to re-locate the line and resume navigation, ensuring it never gets stuck or goes off-course permanently.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Nano.
* **Sensors:** 5-Channel IR Reflectance Sensor Array.
* **Actuators:** High-torque DC Motors with specialized motor drivers.
* **Power:** Li-Po Battery with stable voltage regulation.

## 📂 Project Structure
* `/Firmware`: Contains the Arduino source code (`.ino`) featuring the custom recovery logic and steering states.
* `/Hardware`: Schematics, wiring diagrams, and chassis design details.
* `/Media`: Photos and videos of the robot in action during the competition.

---

### 👨‍💻 Developed by:
**Ahmed Fayez** *AI & Robotics Student at MICA Academy* [Email](mailto:ahmedfayaez21@gmail.com) | [GitHub Profile](https://github.com/AhmedFayez321)
