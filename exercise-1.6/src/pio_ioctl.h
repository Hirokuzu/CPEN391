#ifndef _PIO_IOCTL_
#define _PIO_IOCTL_


#include <linux/ioctl.h>
#include "hps_0.h"
#include "socal/hps.h"

#define MAJOR_NUM 122
#define DEVICE_NAME "pio_ioctl"
#define DEVICE_FILE_NAME "/dev/pio_ioctl"

#define IOCTL_SET_LED _IOW(MAJOR_NUM, 0, char)
#define IOCTL_GET_LED _IOR(MAJOR_NUM, 1, char)
#define IOCTL_GET_DIPSW _IOR(MAJOR_NUM, 2, char)
#define IOCTL_GET_BUTTON _IOR(MAJOR_NUM, 3, char)

#define PIO_REGS_BASE (ALT_LWFPGASLVS_OFST + LED_PIO_BASE)
#define PIO_REGS_SPAN (BUTTON_PIO_END - LED_PIO_BASE + 1)

static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
long device_ioctl(struct file *flip, unsigned int ioctl_num, unsigned long ioctl_param);
int init_module(void);
void cleanup_module(void);

#endif
