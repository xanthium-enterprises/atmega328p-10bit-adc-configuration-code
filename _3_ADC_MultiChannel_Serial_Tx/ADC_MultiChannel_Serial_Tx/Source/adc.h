
#include <util/delay.h>    

// +-----------------------------------------------------------------------+ //
// |   ADC channel definitions for ATmega328p (28 pin and 32pin QFP)       | //
// +-----------------------------------------------------------------------+ //
#define ADC_CHANNEL_0   0b00000000	// ADC0 Channel
#define ADC_CHANNEL_1   0b00000001  // ADC1 Channel
#define ADC_CHANNEL_2   0b00000010	// ADC2 Channel
#define ADC_CHANNEL_3   0b00000011  // ADC3 Channel
#define ADC_CHANNEL_4   0b00000100	// ADC4 Channel
#define ADC_CHANNEL_5   0b00000101  // ADC5 Channel

#define ADC_CHANNEL_6   0b00000110	// ADC6 Channel  Only available in 32 pin TQFP Versions
#define ADC_CHANNEL_7   0b00000111  // ADC7 Channel  Only available in 32 pin TQFP Versions

#define ADC_TEMP_SENSOR 0b00001000  // Internal temp Sensor
#define ADC_GND_0V      0b00001111  // Ground ,0V
// +-----------------------------------------------------------------------+ //



uint16_t read_adc_channel(uint8_t channel_to_read);
void transmit_adc_value(uint16_t adc_10bit_value);
