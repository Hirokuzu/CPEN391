#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include "pio_ioctl_api.h" 

int pio_open(void)
{
    int file_desc = open(DEVICE_FILE_NAME, 0);
    if(file_desc < 0) {
        fprintf(stderr, "PIO failed to open with error %d.\n", file_desc);
    }
    return file_desc;
}

void pio_close(int file_desc)
{
    close(file_desc);
}



int pio_set_led(int file_desc, char led_state)
{
    int ret = ioctl(file_desc, IOCTL_SET_LED, led_state);
    if(ret < 0) {
        fprintf(strerr, "LED writing failed with error code %d.\n", errno);
    }
    return ret;
}

char pio_get_led(int file_desc)
{
    if(!check_fd(file_desc)) return -1;
    char ret = ioctl(file_desc, IOCTL_GET_LED, NULL);
    return ret;
}

char pio_get_dipsw(int file_desc)
{
    if(!check_fd(file_desc)) return -1;
    char ret = ioctl(file_desc, IOCTL_GET_DIPSW, NULL);
    return ret;
}

char pio_get_button(int file_desc)
{
    if(!check_fd(file_desc)) return -1;
    char ret = ioctl(file_desc, IOCTL_GET_BUTTON, NULL);
    return ret;
}

bool check_fd(int file_desc)
{
    if(file_desc < 0)
    {
        fprintf(stderr, "Invalid file descriptor on line %d.\n", __LINE__);
        return false;
    }
    return true;
}

