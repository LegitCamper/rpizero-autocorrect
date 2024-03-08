#include "rpi-gpio.h"

volatile unsigned int *gpio = (unsigned int *)GPIO_BASE;
volatile unsigned int tim;
volatile unsigned int vcount;

void blink_act(volatile unsigned int count, volatile unsigned int wait) {
  /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
     peripheral register to enable GPIO16 as an output */
  gpio[LED_GPFSEL] |= (1 << LED_GPFBIT);

  for (vcount = 0; vcount < count; ++vcount) {
    for (tim = 0; tim < wait; tim++)
      ;

    /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off
       for plus models )*/
    gpio[LED_GPCLR] = (1 << LED_GPIO_BIT);

    for (tim = 0; tim < wait; tim++)
      ;

    /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on
       for plus models )*/
    gpio[LED_GPSET] = (1 << LED_GPIO_BIT);
  }
}
