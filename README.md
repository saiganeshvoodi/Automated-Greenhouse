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

### 1. `sendSensor`
This function reads data from the **DHT11 sensor**, which measures **temperature** and **humidity**. It then sends these readings to the **Blynk app** on virtual pins for real-time monitoring.

- `h = dht.readHumidity();` – Reads the humidity from the DHT11 sensor.
- `t = dht.readTemperature();` – Reads the temperature. You can use `dht.readTemperature(true)` for Fahrenheit.
- `Blynk.virtualWrite(V5, h);` and `Blynk.virtualWrite(V6, t);` – Send the humidity and temperature data to virtual pins V5 and V6 in the Blynk app.

### 2. `sendSensor1`
This function reads data from multiple sensors, such as **MQ135** (air quality), **LM35** (temperature), **MQ2** (gas), **LDR** (light), and **soil moisture sensor**. It also controls the **fan**, **lights**, and **water pump** based on sensor thresholds.

- **Air Quality Control**: If the **MQ135** reading is above 600, it indicates poor air quality. The function activates the fan and sends a notification.
  - `digitalWrite(D5, LOW);` – Turns the fan on.
  - `Blynk.email()` and `Blynk.notify()` – Send an email and notification about poor air quality.

- **Light Control**: The **LDR sensor** checks light levels. If it’s dark, the lights are activated.
  - `digitalWrite(D6, LOW);` – Turns the light on.
  - `Blynk.email()` and `Blynk.notify()` – Notify when lights turn on.

- **Soil Moisture Control**: If the soil moisture is below a certain threshold, it turns on the water pump.
  - `digitalWrite(D4, LOW);` – Activates the water pump.
  - `Blynk.email()` and `Blynk.notify()` – Notify about the pump operation.

This function also writes each sensor’s value to specific virtual pins in Blynk for monitoring.

### 3. `lcddisplay`
Displays each sensor’s data sequentially on Blynk’s **LCD widget** with a delay between each update. This helps provide a visual summary of the key environmental conditions on a single screen.

- **State-based Display**: The function cycles through different display states, updating the LCD to show air quality, temperature, MQ2 value, light level, and soil moisture.
- `lcd.print()` – Displays data on the Blynk LCD widget. The `lcd.clear()` command clears the display before each update to prevent overlapping text.

### 4. `thingspeak`
This function logs data to **ThingSpeak**, a cloud platform for IoT data storage and analysis.

- `ThingSpeak.setField()` – Assigns each sensor reading to specific fields on ThingSpeak.
- `ThingSpeak.writeFields()` – Sends all assigned field data to the specified ThingSpeak channel, which requires a minimum interval of 15 seconds between updates on the free plan.

### 5. `changeMux`
This function controls the **multiplexer** (MUX) to read different analog sensors connected to a single analog input pin.

- `digitalWrite(MUX_A, a);`, `digitalWrite(MUX_B, b);`, and `digitalWrite(MUX_C, c);` – Set the MUX control pins to select a specific input channel for reading.

### Additional Components
- **BlynkTimer `timer`** – Sets up timed intervals for each function (e.g., updating sensors, ThingSpeak, and LCD display).
- **WiFi Connection** – Establishes WiFi connection for sending data to Blynk and ThingSpeak.
- **Notifications** – Uses Blynk notifications and email alerts to inform the user when certain thresholds are exceeded (e.g., poor air quality or low soil moisture).

This code structure allows the greenhouse to autonomously monitor and control environmental conditions, with remote access to real-time data and notifications via Blynk and ThingSpeak.


## References
- [Blynk Documentation](https://docs.blynk.io/)
- [ThingSpeak API](https://thingspeak.com/docs)
- [ESP8266 Documentation](https://www.espressif.com/en/products/socs/esp8266)

