# robot_esp8266

# ESP8266 Robot

## Description
This is a simple robot that can be controlled via a web interface. It uses an ESP8266 microcontroller and a motor driver to control the movement of the robot. The robot can be controlled using a web browser on any device connected to the same network as the ESP8266.

## Hardware
- ESP8266 microcontroller
- Motor driver (L298N or similar)
- DC motors
- Chassis
- Power supply (battery or USB)
- Jumper wires

## Software
- Arduino IDE
- ESP8266 board package

## Software Setup
1. Install the Arduino IDE from the [Arduino website](https://www.arduino.cc/en/software).
2. Install the ESP8266 board package in the Arduino IDE:
   - Open the Arduino IDE.
   - Go to File > Preferences.
   - In the "Additional Board Manager URLs" field, add the following URL: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Click OK.
   - Go to Tools > Board > Boards Manager.
   - Search for "ESP8266" and install the package.

via arduino-cli
```bash
arduino-cli config init
arduino-cli config set board_manager.additional_urls http://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli core update-index
arduino-cli core install esp8266:esp8266
```

## Wiring
| ESP8266 Pin | Motor Driver Pin | Description         |
|-------------|------------------|---------------------|
| D2          | ENA              | Motor A Speed       |
| D3          | IN1              | Motor A Direction   |
| D4          | IN2              | Motor A Direction   |
| D5          | IN3              | Motor B Direction   |
| D6          | IN4              | Motor B Direction   |
| D7          | ENB              | Motor B Speed       |
| GND         | GND              | Ground              |

Use the +12V power supply to power the motor driver. The ESP8266 can be powered via USB or a battery.

## Building and Uploading
via arduino-cli
```bash
arduino-cli compile --fqbn esp8266:esp8266:nodemcuv2 src/wifi_bot/wifi_bot.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp8266:esp8266:nodemcuv2 src/wifi_bot/wifi_bot.ino
```

## Debug and checking ip address
```bash
arduino-cli monitor -p /dev/ttyUSB0 --fqbn esp8266:esp8266:nodemcuv2
```

