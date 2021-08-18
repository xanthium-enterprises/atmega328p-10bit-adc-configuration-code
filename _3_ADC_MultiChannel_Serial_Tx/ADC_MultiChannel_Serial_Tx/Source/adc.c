
//===========================================================================//
//       ATmega328P                                                          //
//      +---------------+                                                    //
//      |           PC0 |<----> AN1                                          //
//      |           PC1 |<----> AN2                                          //
//      |           PC2 |<----> AN3                                          //
//      |           PC3 |<----> AN4                                          //
//		|  PC4/ADC4/SDA |<----> (D23)[RESET_LED]                             //
//      |  PC5/ADC5/SCL |<---->(1)[J12]                                      //
//      |           ADC6|<-----(2)[J12]                                      //
//      |           ADC7|<-----(3)[J12]                                      //
//      +---------------+                                                    //
//                                                                           //
//---------------------------------------------------------------------------//

#include <stdint.h>
#include <avr/io.h>

#include "adc.h"



//Takes an ADC channel as parameter ->"channel_to_read"
//and returns the converted 10bit value of that channel in a 16 bit Variable
uint16_t read_adc_channel(uint8_t channel_to_read)
{
	
	volatile uint16_t ADC_10bit_result = 0;
	
	// ATmega328p ADC Configuration Code
	
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Select ADC Prescalar to 128,11.0598MHz/128 = 85KHz
	
	ADMUX   = ADMUX & 0xF0;   // Clear the lower bits MUX0-MUX3 of ADMUX,Will cause problems when channels are changed if not cleared                                               
	
	//ADMUX  |= (1<<REFS0) | (1<<REFS1) ; // Select Vref = 1.1V internal since AREF pin of ATmega328P is connected to capacitor
	ADMUX  |= (1<<REFS0);                 // Select Vref = AVcc= 5V internal since AREF pin of ATmega328P is connected to capacitor
	
	                                    // if AREF pin is connected directly to 5V, comment out the above line
	ADMUX  |= channel_to_read;          // Select the ADC channel to convert
	
	ADCSRA |= (1<<ADEN)  | (1<<ADSC);                // Enable ADC and Start the conversion
	
	while( !(ADCSRA & (1<<ADIF)) );                  // Wait for conversion to finish
	
	// When ADIF not Set,	[(ADCSRA & (1<<ADIF) = 0]
	//	So NOT[(ADCSRA & (1<<ADIF) ] = 1, While(loop is true),Stays there

	
	// When ADIF is Set,	[(ADCSRA & (1<<ADIF) = 1]
	//	So NOT[(ADCSRA & (1<<ADIF) ] = 0, While(loop is false),Exits and goes to next instruction
	
	
	
	ADC_10bit_result   =  ADC;      // "ADC" variable (AVR-GCC defined variable) Contains the whole 10 bit ADC result,
	                                // stored in the 16 bit ADC_10bit_Result Variable  (unsigned int)
	
	ADCSRA |= (1<<ADIF);            // Clear ADIF,ADIF is cleared by writing a 1 to ADSCRA (According to ATmega328p datasheet)
	
	
	
	//ADCSRA &= ~(1<<ADEN);			
    					
	return ADC_10bit_result ;
}

//Transmits the 10bit value using USART in text format
// sends \n after text 
void transmit_adc_value(uint16_t adc_10bit_value)
{
	//splitting the value to individual digits 1000's  100's  10's  1's   position
	// we will use 1023(decimal) as an eg        1       0      2     3
	// eg adc_value = 1023 decimal
	
	uint16_t  temp = 0; //Temporary Storage (16bit)
	
	uint8_t   Ones_Position = 0;		// 8 bit variables to be send using usart
	uint8_t   Tens_Position = 0;
	uint8_t   Hundreths_Position =0;
	uint8_t   Thousands_Position =0;
	
	temp = adc_10bit_value;
	
	Ones_Position      = temp % 10; // Eg 1023 % 10  -> Remainder -> 3
	temp = temp/10;                 // Eg temp = 1023/10 ->102
	Tens_Position      = temp % 10; // Eg 102  % 10  -> Remainder -> 2
	temp = temp/10;                 // Eg temp = 102/10 ->10
	Hundreths_Position = temp % 10;  // Eg 10   % 10  -> Remainder -> 0
	Thousands_Position = temp / 10;  // Eg 10   / 10  -> Quotient  -> 1
	
	//ASCII Conversion
	Ones_Position += 0x30;
	Tens_Position += 0x30;
	Hundreths_Position += 0x30;
	Thousands_Position += 0x30;
	
	//Sending the 4 digit number to PC using USART
	
	trasmit_usart_data(Thousands_Position);
	trasmit_usart_data(Hundreths_Position);
	trasmit_usart_data(Tens_Position);
	trasmit_usart_data(Ones_Position);
	
	
}



