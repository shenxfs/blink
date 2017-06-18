#include "main.h"
int16_t main(void)
{
  volatile uint8_t tmp;
  volatile uint8_t instatus=0;
  volatile uint8_t status = RST_STA;
  LED_PORT = LED_MASK;
  LED_DDR  = LED_MASK;

  RESET_PORT &= ~_BV(RESET);
  RESET_DDR &= ~_BV(RESET);

  FLASH_PORT &= ~_BV(FLASH);
  FLASH_DDR &= ~_BV(FLASH);
  tmp = 1U;
  while(tmp != 0)
  {
    LED_PORT &= ~tmp;
    __builtin_avr_delay_cycles(HALF_SENCOND);
    LED_PORT = LED_MASK;
    tmp <<= 1U;
  }
  while(1)
  {
    instatus = get_status();
    if(((instatus^status) != 0) &&(instatus != IDL_STA))
    {
      status = instatus;
    }
    if(status == RST_STA)
    {
      LED_PORT = LED_MASK;
      tmp = 0;
    }
    else
    {
      if(status == FLS_STA)
      {
        if(tmp == 10)
        {
          LED_PORT ^= _BV(LED1_PIN)|_BV(LED3_PIN)|_BV(LED5_PIN)|_BV(LED7_PIN);
          tmp = 0;
        }
        tmp++;
      }
    }
  }
}

uint8_t get_status(void)
{
  uint8_t ret = IDL_STA;
  uint8_t i;
  volatile uint8_t key_sta = 0;
  if((!(RESET_PININ & _BV(RESET)))&&(!(FLASH_PININ & _BV(FLASH))))
  {
    __builtin_avr_delay_cycles(TWENTY_MSEC);
    if((!(RESET_PININ & _BV(RESET)))||(!(FLASH_PININ & _BV(FLASH))))
    {
      ret = RST_STA;
      key_sta =1U;
    }
    else if(!(RESET_PININ & _BV(RESET)))
    {
      ret = RST_STA;
      key_sta =1U;
    }
    else if(!(FLASH_PININ & _BV(FLASH)))
    {
      ret = FLS_STA;
      key_sta =1U;
    }
  }
  else if(!(RESET_PININ & _BV(RESET)))
  {
    __builtin_avr_delay_cycles(TWENTY_MSEC);
    if(!(RESET_PININ & _BV(RESET)))
    {
      ret = RST_STA;
      key_sta = 1U;
    }
  }
  else
  {
     if(!(FLASH_PININ & _BV(FLASH)))
     {
       __builtin_avr_delay_cycles(TWENTY_MSEC);
       if(!(FLASH_PININ & _BV(FLASH)))
       {
         ret = FLS_STA;
         key_sta = 1U;
       }
     }
  }
  i = 0;
  if(key_sta != 0)
  {
    do
    {
      __builtin_avr_delay_cycles(TWENTY_MSEC);
      if(((RESET_PININ & _BV(RESET)) == _BV(RESET))
        &&((FLASH_PININ & _BV(FLASH)) == _BV(FLASH)))
      {
        break;
      }
      i++;
    } while(i<10);
  }
  else
  {
      __builtin_avr_delay_cycles(TWENTY_MSEC);
  }
  return ret;
}
