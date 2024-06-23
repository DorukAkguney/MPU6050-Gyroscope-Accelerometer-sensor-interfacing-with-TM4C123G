# TM4C123G with MPU6050 for Gyroscope and Accelerometer Data Collection

## Project Overview
This project involves interfacing the TM4C123G Tiva C Launchpad with the MPU6050 sensor to read gyroscope and accelerometer data and transmit it to a computer via UART.

## Components
- TM4C123G Tiva C Launchpad
- MPU6050 Gyroscope and Accelerometer Sensor
- USB to Serial Converter
- Connecting wires

## Hardware Connections
1. **MPU6050 to TM4C123G Tiva C Launchpad:**
   - VCC to 3.3V
   - GND to GND
   - SDA to PA7
   - SCL to PA6

2. **TM4C123G Tiva C Launchpad to USB to Serial Converter:**
   - PE4 (UART5_RX) to RX
   - PE5 (UART5_TX) to TX
   - GND to GND

## Software Implementation
### I2C Initialization
```c
void I2C_Init(void) {
    // Enable I2C and GPIO clocks
    // Configure GPIO pins for I2C
    // Set I2C speed to 100 kHz
}
