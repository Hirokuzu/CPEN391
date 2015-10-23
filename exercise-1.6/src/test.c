#include<stdio.h>
#include"pio_ioctl_api.h"

int main()
{
	char led_val, old_led_val, dipsw_val, old_dipsw_val, button_val;
	int file_desc, err;
	printf("DE0-nano SoC PIO driver test program\n");
	printf("------------------------------------\n");
	printf("LED = DIPSW && !BUTTON\n");
	old_led_val = 0;
	old_dipsw_val = 0;
	while(1)
	{
		file_desc = pio_open();
		dipsw_val = pio_get_dipsw(file_desc);
		if(dipsw_val != old_dipsw_val)
		{
			printf("dipsw value = %d\n", dipsw_val);
			old_dipsw_val=dipsw_val;
		}
		button_val = pio_get_button(file_desc);
		if(button_val == 3)
			err = pio_set_led(file_desc, dipsw_val);
		else
			err = pio_set_led(file_desc, 0);
		led_val = pio_get_led(file_desc);
		if(led_val != old_led_val)
		{
			printf("New LED value = %d\n\n", led_val); 
			old_led_val = led_val;
		}
		pio_close(file_desc);
	}
	
}
