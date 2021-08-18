
#include <stdint.h>
#include <avr/io.h>


// +-----------------------------------------------------------------------+ //
// | ATmega328p Baud rate values for UBRRn for external crystal 11.0592MHz  | //
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



void configure_serial_usart(unsigned int baudrate);
void trasmit_usart_data(uint8_t transmit_byte);

