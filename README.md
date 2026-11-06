# Home Safety Monitoring System Using ESP32

## Project Description
The Home Safety Monitoring System is an IoT-based embedded project developed using the ESP32 microcontroller. It monitors indoor temperature, humidity, and human movement using DHT22 and PIR sensors.

The system provides real-time sensor information through an OLED display. When abnormal environmental conditions or motion are detected, it activates an LED and buzzer to provide alerts. A relay module is used to control an external load during high-temperature or high-humidity conditions.

## Hardware Components
- ESP32 Development Board
- DHT22 Temperature and Humidity Sensor
- PIR Motion Sensor
- OLED Display (SSD1306)
- LED
- Buzzer
- Relay Module

## Software and Libraries
- Arduino IDE
- Embedded C/C++
- DHT Sensor Library
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Wire Library

## Key Features
- Real-time temperature monitoring
- Humidity monitoring
- Human motion detection
- OLED-based status display
- Audio and visual alerts
- Relay-based output control

## Working Principle
The ESP32 reads temperature and humidity values from the DHT22 sensor and detects movement through the PIR sensor. It compares sensor readings with predefined safety thresholds and controls the alert devices accordingly.

## Applications
- Smart home monitoring
- Indoor environmental monitoring
- Basic home security systems
- Embedded safety automation

## Future Improvements
- Wi-Fi-based mobile notifications
- Cloud-based sensor data monitoring
- Smoke and gas detection
- Improved alert management