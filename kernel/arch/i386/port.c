#include <stdint.h>

#include "port.h"
 
  
void byte_out(uint16_t port, unsigned char data) {
  __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned char byte_in(uint16_t port) {
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

