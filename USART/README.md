# USART CLI for STM32

This project demonstrates how to use USART communication in an STM32 microcontroller to implement a simple Command Line Interface (CLI). The CLI allows users to send commands via a serial terminal (such as HTerm or PuTTY) to control on-board peripherals, such as turning LEDs on and off.

**Features**
* USART-based command-line interface (CLI)

* Example command: turn_on green_led to turn on the green LED

* Supports basic text-based communication between STM32 and a serial terminal

* Easily extendable to add more commands

**Hardware Requirements**

* STM32 development board (e.g., STM32F4xx, STM32F1xx, etc.)

* USB-to-Serial adapter (if needed)

* A terminal emulator (HTerm, PuTTY, or Tera Term)

**Software Requirements**

* STM32CubeIDE or Keil uVision

* STM32 HAL Library
* Serial terminal emulator
