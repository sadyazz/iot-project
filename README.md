# IoT Home Automation Project

## Description

This project is an IoT-based home automation system using ESP8266 and various sensors. It includes a web interface for remote control of lights and monitoring of gas levels, connected to a Firebase Realtime Database for communication and status updates.

The project consists of three main components:

1. **Control Side**: A web application (HTML, CSS, and JavaScript) for remote control.

2. **Execution Side**:  Implemented using an ESP8266 microcontroller, equipped with the following components:
   
- PIR Motion Sensor: Detects motion and controls one of the LEDs.
  
- LDR (Light Dependent Resistor): Senses ambient light levels and controls an LED, providing automatic outdoor lighting.
  
- MQ2 Gas Sensor: Detects gas levels in the environment and triggers the buzzer when gas is detected.
  
- Buzzer: An audio signaling device that audibly alerts the user when the gas sensor detects a gas leak.
  
- LEDs: Three LEDs are used in the project. One is controlled via the website, representing a room light. The second is connected to the PIR motion sensor and represents a garage light, providing automatic lighting. The third is connected to the LDR, representing an outdoor light.

3. **Real-time Database**: Utilizes Google's Firebase service to create a real-time database. This database enables communication between the control panel and the execution side, ensuring seamless control and monitoring of home devices.

## Functionalities

The system offers the following functionalities:

**Automatic Lighting**

The project includes two LEDs that are controlled by sensors for automatic lighting. One LED is connected to a PIR motion sensor, providing automatic lighting when motion is detected. The other LED is connected to an LDR, offering automatic outdoor lighting based on ambient light levels.

**Light Status Display**

The web interface provides real-time status updates for all LEDs. Users can monitor the status of each light and control them remotely via the interface.

**Gas Leak Detection**

The project includes an MQ2 gas sensor that detects gas leaks. When a gas leak is detected, a buzzer is triggered to alert the user.

**Real-time Alerts**

In addition to the audible buzzer alert, users receive real-time alerts on the web interface when gas is detected.
