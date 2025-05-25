# Line Follower Robot with Obstacle Detection

**Author:** Md. Tasin Absar 
**Course:** CSE-1121  
**Semester:** 1st Semester, May 2024  
**Project:** Semester Final Project  

---

## Project Overview

This project presents a **Line Follower Robot with Obstacle Detection** built using an Arduino microcontroller. The robot is designed to autonomously follow a predefined black line on a white surface, using infrared sensors, while simultaneously detecting and avoiding obstacles in its path through ultrasonic sensing.

---

## Key Features

- **Line Following:** The robot uses infrared (IR) sensors to detect and follow a black line on the ground, enabling it to navigate a set path accurately.
- **Obstacle Detection:** An ultrasonic sensor monitors the front environment to detect obstacles and prevent collisions by stopping or avoiding them.
- **Arduino Based Control:** The entire system is controlled using an Arduino board programmed in the Arduino IDE.
- **Real-Time Decision Making:** Combines sensor inputs for dynamic and real-time navigation control.

---

## Components Used

- Arduino Uno
- Infrared line sensors
- Ultrasonic distance sensor
- DC motors with motor driver
- Chassis, wheels, and power supply components  

---

## How It Works

1. The IR sensors detect the contrast between the line and the background.  
2. Based on sensor inputs, the Arduino adjusts motor speeds to keep the robot aligned with the line.  
3. The ultrasonic sensor continuously scans ahead; if an obstacle is detected within a certain range, the robot stops or takes corrective action.  
4. Once the obstacle is cleared, the robot resumes line following.

---

## Project Structure

- `Line_Follower_Obstacle.ino` — Main Arduino sketch controlling robot behavior  
- `README.md` — Project description and instructions  
- Additional files related to wiring diagrams, schematics, or documentation  

---

## Usage Instructions

1. Assemble the robot hardware according to the wiring diagrams.  
2. Upload the Arduino code (`Line_Follower_Obstacle.ino`) to the Arduino board using the Arduino IDE.  
3. Power the robot and place it on a surface with a clearly marked black line.  
4. The robot will start following the line and stop or avoid obstacles automatically.  

---

## Learning Outcomes

- Practical understanding of sensor integration with microcontrollers  
- Experience in programming embedded systems for autonomous behavior  
- Fundamentals of robotics including path following and obstacle avoidance  
- Hands-on application of control logic and sensor fusion  

---

## Acknowledgments

This project was completed as the **final project** for the **CSE-1121 course, 1st semester, May 2024**.
