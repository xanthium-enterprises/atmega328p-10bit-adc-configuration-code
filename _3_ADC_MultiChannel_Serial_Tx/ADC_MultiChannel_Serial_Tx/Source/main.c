
//Configure Multiple channels of ADC and Send that data to PC


//=======================================================================================//
//                                                                                       //
//                 +------------------+                                                  //
//                 |                  |                                                  //
// ANALOG_Ch_1---->| PC0              |                                                  //
// ANALOG_Ch_2---->| PC1              |                                                  //
// ANALOG_Ch_3---->| PC2              |                                                  //
// ANALOG_Ch_4---->| PC3              |                                                  //
//                 |                  |                                                  //
//                 |                  |                                                  //
//                 +------------------+                                                  //
//---------------------------------------------------------------------------------------//


//+---------------------------------------------------------------------------------------+
//| Compiler           : ATMEL Studio                                                     |
//| Microcontroller    : ATmega328p                                                       |
//| Crystal Frequency  : External,11.0592MHz                                              |
//| Programmer         : Rahul.Sreedharan                                                 |
//| Date               : 18-Aug-2021                                                      |
//+---------------------------------------------------------------------------------------+

 //(C) www.xanthium.in
 // Visit to Learn More                
 //https://www.xanthium.in/atmega328p-10bit-sar-adc-usart-serial-transmit-to-pc-data-acquisition-tutorial
 

 //Crystal Frequency and Delay Config
 #define F_CPU 11059200    //Should be defined above #include <util/delay.h>
 #include <util/delay.h>    
 
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h> // Required to declare the ISR Macro for interrupts            


#include "adc.h"
#include "serial_usart.h"




int main(void)
{
	 configure_serial_usart(BAUD_RATE_9600_BPS);
	 
	 
	 while(1)
	 {
	
	   transmit_adc_value(read_adc_channel(ADC_CHANNEL_0));
	   trasmit_usart_data('-');
	   // _delay_ms(100);
		
	   transmit_adc_value(read_adc_channel(ADC_CHANNEL_1));
	   trasmit_usart_data('-');
	   // _delay_ms(100);
		
	   transmit_adc_value(read_adc_channel(ADC_CHANNEL_2));
	   trasmit_usart_data('-');
	   // _delay_ms(100);
	   transmit_adc_value(read_adc_channel(ADC_CHANNEL_3));
	   trasmit_usart_data('\n');
	   _delay_ms(1000);
		
		 
	 }
}//End of main()


