


#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h> // Required to declare the ISR Macro for interrupts

#include"serial_usart.h"
#include <util/delay.h>  




void configure_serial_usart(unsigned int baudrate)
{
	unsigned int ubrr =  baudrate;
	
	
	/******************  USART Configuration code ************************/
	
	/* Set Baudrate  */
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = 0x06;
	
	/*********************************************************************/
	
}//end of configure_serial_usart();



void trasmit_usart_data(uint8_t transmit_byte)
{	
	UCSR0B |= (1<<TXEN0);            // Enable transmitter
	while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       
	UDR0 = transmit_byte;		     // Put data into buffer, sends the data 
	while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer 
}




