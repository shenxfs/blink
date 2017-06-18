#ifndef MAIN_H
#define MAIN_H
#include <avr/io.h>

#define LED_PORT      PORTD
#define LED_DDR       DDRD
#define LED1_PIN      0
#define LED2_PIN      1
#define LED3_PIN      2
#define LED4_PIN      3
#define LED5_PIN      4
#define LED6_PIN      5
#define LED7_PIN      6
#define LED8_PIN      7
#define LED_MASK      0xff

#define RESET_PORT    PORTC
#define RESET_DDR     DDRC
#define RESET_PININ   PINC
#define RESET         5

#define FLASH_PORT    PORTB
#define FLASH_DDR     DDRB
#define FLASH_PININ   PINB
#define FLASH         2

#define HALF_SENCOND  (F_CPU/2)
#define TWENTY_MSEC   (F_CPU/50)
#define IDL_STA       0
#define RST_STA       1U
#define FLS_STA       2U

uint8_t get_status(void);

#endif
