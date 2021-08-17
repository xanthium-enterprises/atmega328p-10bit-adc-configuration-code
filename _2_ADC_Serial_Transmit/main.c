

// AVR ADC UART DATA Transmission 
// AVR reading the state of ADC7 ,POT connected to ADC7 Input,1K resistor in series with ADC7 input
// External Oscillator = 11.0592MHz
// Controller ATmega328p


//+------------------------------------------------------------------------------------------------+
//| Compiler           : AVR GCC (WinAVR)                                                          |
//| Microcontroller    : ATmega328p                                                                |
//| Programmer         : Rahul.Sreedharan                                                          |
//| Date               : 11-April-2019                                                             |
//+------------------------------------------------------------------------------------------------+

//(C) www.xanthium.in 
// Visit to Learn More 


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// +-----------------------------------------------------------------------+ //
// | ATmega328p Baudrate values for UBRRn for external crystal 11.0592MHz  | //
// +-----------------------------------------------------------------------+ //

#define BAUD_RATE_4800_BPS  143 // 4800bps
#define BAUD_RATE_9600_BPS  71  // 9600bps

#define BAUD_RATE_14400_BPS  47 // 14.4k bps
#define BAUD_RATE_19200_BPS  35 // 19.2k bps  
#define BAUD_RATE_28800_BPS  23 // 28.8k bps
#define BAUD_RATE_38400_BPS  17 // 38.4k bps
#define BAUD_RATE_57600_BPS  11 // 57.6k bps
#define BAUD_RATE_76800_BPS   8 // 76.8k bps

#define BAUD_RATE_115200_BPS  5 // 115.2k bps
#define BAUD_RATE_230400_BPS  2 // 230.4k bps

// +-----------------------------------------------------------------------+ //



// +-----------------------------------------------------------------------+ //
// |   ADC channel definitions for ATmega328p (28 pin and 32pin QFP)       | //
// +-----------------------------------------------------------------------+ //
#define ADC_Channel_0   0b00000000	// ADC0 Channel 
#define ADC_Channel_1   0b00000001  // ADC1 Channel 
#define ADC_Channel_2   0b00000010	// ADC2 Channel 
#define ADC_Channel_3   0b00000011  // ADC3 Channel 
#define ADC_Channel_4   0b00000100	// ADC4 Channel 
#define ADC_Channel_5   0b00000101  // ADC5 Channel 

#define ADC_Channel_6   0b00000110	// ADC6 Channel Only available in 32 pin TQFP Versions
#define ADC_Channel_7   0b00000111  // ADC7 Channel Only available in 32 pin TQFP Versions

#define ADC_Temp_Sensor 0b00001000  // Internal temp Sensor
#define ADC_GND_0V      0b00001111  // Ground ,0V
// +-----------------------------------------------------------------------+ //

// Note:
// Using ADCL or ADCH  for reading from ADC data register may cause unpredictable issues,If Correct order is not followed.
// like RESETing the ATmega328 every time to get the correct result.
// This is caused due to incorrect access to ADCL and ADCH registers

int main()
{
	void Reset_LED_Beep();
	
	uint8_t  ADC_8bit_High_Byte = 0; // unsigned int 8 bit variable to get the ADC High Byte
	uint8_t  ADC_8bit_Low_Byte  = 0; // unsigned int 8 bit variable to get the ADC Low Byte
	uint16_t ADC_10bit_Result = 0;   // unsigned int 16 bit variable to store the 10 bit ADC  value
	
	
	// USART configuration 
	
	uint16_t ubrr = BAUD_RATE_230400_BPS;
	
	/* Set Baudrate  */
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	/*Enable transmitter */
	UCSR0B = (1<<TXEN0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = 0x06;
	
	
	
	while(1)  // Continously read ADC every 1 second 
	{
		
		// ATmega328p ADC Configuration Code 
		
		ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);  // Select ADC Prescalar to 128,11.0598MHz/128 = 85KHz
		
		//ADMUX  |= (1<<REFS0) ;                           // if CAP connected to AREF pin,Vref =internal AVcc,
		//ADMUX  |= (1<<REFS0) | (1<<REFS1);               // if CAP connected to AREF pin,Vref =1.1V internal ,
		
		ADMUX  |= ADC_Channel_0;                         // No CAP connected,AREF tied to +5V
		
		ADCSRA |= (1<<ADEN)  | (1<<ADSC);                // Enable ADC and Start the conversion
	
		while( !(ADCSRA & (1<<ADIF)) );                  // Wait for conversion to finish
		
														 // When ADIF not Set,	[(ADCSRA & (1<<ADIF) = 0]
	                                                     //	So NOT[(ADCSRA & (1<<ADIF) ] = 1, While(loop is true),Stays there

														 
														 // When ADIF is Set,	[(ADCSRA & (1<<ADIF) = 1]
	                                                     //	So NOT[(ADCSRA & (1<<ADIF) ] = 0, While(loop is false),Exits and goes to next instruction
														 
		
		
		ADC_10bit_Result   =  ADC;      // "ADC" variable (AVR-GCC defined variable) Contains the whole 10 bit ADC result,
		                                // stored in the 16 bit ADC_10bit_Result Variable  (unsigned int)
										
		//ADC_8bit_Low_Byte   = ADCL;   // Read the 8 bit ADCL first,then ADCH
		//ADC_8bit_High_Byte  = ADCH;   // Order have to be maintained,
		                                // otherwise ADC result may get locked and will not change
									    // without a AVR chip reset.				
		
		
		ADCSRA |= (1<<ADIF);            // Clear ADIF,ADIF is cleared by writing a 1 to ADSCRA (According to ATmega328p datasheet)
		
		//splitting the value to individual digits 1000's  100's  10's  1's   position
        // we will use 1023(decimal) as an eg        1       0      2     3 
        // eg adc_value = 1023 decimal
		
		uint16_t  temp = 0; //Temporary Storage (16bit)
		
		uint8_t   Ones_Position = 0;		// 8 bit variables to be send using usart
		uint8_t   Tens_Position = 0;
		uint8_t   Hundreths_Position =0;
		uint8_t   Thousands_Position =0;
		
		temp = ADC_10bit_Result;
		
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
		
        while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       */
		UDR0 = Thousands_Position;		 // Put data into buffer, sends the data */
		
		while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       */
		UDR0 = Hundreths_Position;		 // Put data into buffer, sends the data */
		
		
		while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       */
		UDR0 = Tens_Position;		 // Put data into buffer, sends the data */
		
		while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       */
		UDR0 = Ones_Position;		 // Put data into buffer, sends the data */

		// Send '-' Character //
		while (!( UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer       */
		UDR0 = '-';	
	
		_delay_ms(1000);
	}
	
	
	
	
	
}//end of main




















