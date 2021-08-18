# AVR ATmega328p 10 bit ADC Configuration and PC serial communication tutorial

 - The tutorial teaches the user to configure the 10 bit SAR ADC of ATmega328P in Embedded C and transmit the ADC result to Linux /Windows PC using USART and a USB to Serial Converter.

 - **ADC6** and **ADC7** channels are only available in the 32 pin TQFP version of ATmega328P chip.

 - Tutorial deals in **Single Channel** conversionas well as configuring **multiple channels** of ATmega328P ADC

<img src = "https://www.xanthium.in/sites/default/files/site-images/atmega328p-adc-config-tutorial/atmega32-adc-data-acquisution-tutorial.jpg"/>

## Code

- Sourcecode written in **Embedded C**. 
- Compiled using **AVR-GCC** using **Make** utility.
- Code can be uploaded using AVRDUDE and any compatible programmer.

## Hardware setup

- Code tested on ATmega328p (32 pin TQFP).
- ATmega328p Clocked with a **11.0592MHz external crystal**.
- USB to Serial Converter used to connect ATmega328p with PC 
- PuTTY used to receive and Transmit data
- <img src = "https://www.xanthium.in/sites/default/files/site-images/atmega328p-adc-config-tutorial/atmega328p-adc-data-serial-putty.jpg"/>

## ATmega328p Clocking (Fuse Bits)
- External 11.0592MHz Crystal
- *avrdude -c usbasp -p m328p -U lfuse:w:0xFF:m*

## Online Documentation

- <a href="https://www.xanthium.in/how-to-configuring-atmega328p-fuse-low-byte-embedded-design-use-external-crystal-fuse-settings">Configuring the ATmega328p 10 bit ADC and transmitting the results to a PC</a>

- <a href="https://www.xanthium.in/how-to-configuring-atmega328p-fuse-low-byte-embedded-design-use-external-crystal-fuse-settings">Configuring the ATmega328p Microcontroller to use external crystal</a>

- <a href ="https://www.xanthium.in/how-to-avr-atmega328p-microcontroller-usart-uart-embedded-programming-avrgcc">ATmega328p USART serial communication tutorial</a>

- <a href="https://www.xanthium.in/USB-to-Serial-RS232-RS485-Converter">USB to Serial/RS232/RS485 Converter</a>

- www.xanthium.in


