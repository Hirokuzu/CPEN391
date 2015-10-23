#ifndef _PIO_IOCTL_
#define _PIO_IOCTL_


#include <linux/ioctl.h>
#include "hps_0.h"

#define MAJOR_NUM 122
#define DEVICE_NAME "pio_ioctl"
#define DEVICE_FILE_NAME "/dev/pio_ioctl"



static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
long device_ioctl(struct file *flip, unsigned int ioctl_num, unsigned long ioctl_param);
int init_module(void);
void cleanup_module(void);

#endif