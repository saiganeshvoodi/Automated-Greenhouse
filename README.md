# Automated Greenhouse

An IoT-based greenhouse automation project using ESP8266, DHT11, MQ sensors, Blynk, and ThingSpeak. This project monitors environmental parameters and automates control systems like fans, pumps, and lights for optimal plant growth.

## Getting Started

- Clone the repository
- Add your credentials to the `config.json` file (use `config.example` as a guide)
- Upload the code to your ESP8266 device

For full instructions, please refer to the main README file.

---

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [References](#references)

## Introduction
The Automated Greenhouse monitors environmental conditions like air quality, temperature, light, and soil moisture to automatically control devices within the greenhouse. It sends real-time data to Blynk and ThingSpeak for easy monitoring and notifications.

## Features
- Real-time monitoring of:
  - Temperature and humidity
  - Air quality (MQ-135)
  - Light levels
  - Soil moisture
- Automatic control of:
  - Fan (based on air quality and temperature)
  - Pump (based on soil moisture)
  - Lights (based on light sensor readings)
- Notifications and alerts via Blynk for critical levels.
- Data logging to ThingSpeak for analysis.

## Hardware Requirements
- ESP8266
- DHT11 Sensor
- MQ-135 Air Quality Sensor
- LM35 Temperature Sensor
- MQ-2 Gas Sensor
- Soil Moisture Sensor
- LDR Sensor
- Relay Module for Fan, Pump, and Lights
- Jumper Wires

## Software Requirements
- Arduino IDE
- Blynk App
- ThingSpeak account

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/your_username/automated-greenhouse.git
   cd automated-greenhouse
2. Install required libraries:

   - ESP8266WiFi
   - BlynkSimpleEsp8266
   - DHT
3. Open the code file in Arduino IDE and enter your WiFi credentials and Blynk Auth Token.
4. Upload the code to your ESP8266.

## Usage
- After uploading the code to the ESP8266, open the Serial Monitor to check sensor readings and see status updates.
- Use the Blynk app to monitor data in real-time and receive alerts for changes in environmental parameters.

## Code Explanation
- **sendSensor**: Collects and sends DHT11 readings (temperature and humidity) to Blynk.
- **sendSensor1**: Reads data from MQ sensors and the soil moisture sensor, then sends this data to Blynk.
- **thingspeak**: Writes sensor data to ThingSpeak for logging and further analysis.
- **lcddisplay**: Displays real-time sensor data on the LCD widget within the Blynk app.

## References
- [Blynk Documentation](https://docs.blynk.io/)
- [ThingSpeak API](https://thingspeak.com/docs)
- [ESP8266 Documentation](https://www.espressif.com/en/products/socs/esp8266)

