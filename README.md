# plant_caretaker
Arduino project used to monitor the state of a plant using different parameters, such as humidity or light

This repository contains the design and source code for an Arduino-based robotics project dedicated to plant maintenance. The system automates irrigation and environmental positioning to optimize growth conditions.

## Project Description
This system is an integrated solution for indoor gardening that utilizes an Arduino Uno to monitor soil health and light exposure. Unlike traditional stationary planters, this project features a motorized base that allows the plant to interact with its environment.

The system measures soil moisture using a capacitive sensor to avoid oxidation and uses Light Dependent Resistors (LDRs) to track sun exposure. When the soil becomes dry, the system activates a water pump. Additionally, two servomotors adjust the orientation of the entire base to ensure the plant receives maximum sunlight.

## Hardware Components
Microcontroller: Arduino Uno.

Soil Sensor: Capacitive Soil Moisture Sensor.

Light Sensors: Four Photoresistors (LDR).

Display: 16x2 LCD Screen.

Actuators:

- One Submersible Water Pump.

- Two Servomotors for a 2-Axis movement base.

Power Supply: 9V Battery.

## System Functionality
- Environmental Monitoring: The Arduino reads analog signals from the capacitive sensor and the LDRs.

- Automated Irrigation: If the moisture level falls below a programmed threshold, the water pump is triggered to deliver a specific volume of water.

- Solar Tracking: The two servomotors compare the difference between the LDR readings to rotate and tilt the base towards the strongest light source.

- Data Visualization: The LCD provides a real-time dashboard displaying current moisture percentages.

- Portability: The circuit is optimized for 9V battery operation, allowing for placement in various indoor locations without cables.

## Installation and Setup
- Hardware Assembly: Connect the components according to the wiring diagrams provided in the repository.

- Calibration: Use the calibration script to determine the dry and wet thresholds of your capacitive sensor.

- Software Upload: Open the main source code in the Arduino IDE and upload it to the board.

- Deployment: Place the plant on the motorized base and insert the sensors into the soil.

## Future Improvements
- Implementation of a low-power mode to extend battery life.

- Integration of a water level sensor for the reservoir.

- WiFi connectivity for remote monitoring.
