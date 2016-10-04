#include "io.h"
 
#define BLINK_DELAY_MS 1000
 
int main (void)
{
 /* Set pin 13 to output */
 set_pin_mode(P13, OUTPUT);

 while(1) {
  /* Set pin 13 high to turn led on */
  digital_write(P13, HIGH);
  _delay_ms(BLINK_DELAY_MS);
   
  /* Set pin 13 low to turn led off */
  digital_write(P13, LOW);
  _delay_ms(BLINK_DELAY_MS);
 }
}
