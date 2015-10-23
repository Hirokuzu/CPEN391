#ifndef __PIO_IOCTL_API__
#define __PIO_IOCTL_API__

#include "pio_ioctl.h"

int pio_open(void);
void pio_close(int file_desc);

int pio_set_led(int file_desc, char led_state);
char pio_get_led(int file_desc);
char pio_get_dipsw(int file_desc);
char pio_get_button(int file_desc);

#endif