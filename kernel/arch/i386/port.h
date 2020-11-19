#ifndef _KERNEL_PORT_H
#define _KERNEL_PORT_H

#include <stdint.h>

void byte_out(uint16_t port, unsigned char data);
unsigned char byte_in(uint16_t port);

#endif
