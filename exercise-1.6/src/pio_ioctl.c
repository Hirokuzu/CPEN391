#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <asm/io.h>
#include "/usr/include/socal/hps.h"
#include "hps_0.h"
#include "pio_ioctl.h"

#define OK 0

static int Device_Open=0;
static int Major;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("User-level access to FPGA IOs");

//Mapped memory base address
unsigned long virtual_base;
volatile static char* led;
volatile static char* dipsw;
volatile static char* button;
//Memory sink when not in use
static unsigned long sink;

//Required function address structure
struct file_operations fops = {
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
	.release = device_release
};

//Open device for i/o operations
static int device_open(struct inode *inode, struct file *flip)
{
	// check if device in use
	if(Device_Open)
		return -EBUSY;
	Device_Open++; // call dibs

	// set up memory
	virtual_base = (unsigned int) ioremap(PIO_REGS_BASE, PIO_REGS_SPAN);	
	led = virtual_base;
	dipsw = virtual_base + 0x20;
	button = virtual_base + 0x40;

	// attempt to get device from kernel
	try_module_get(THIS_MODULE);
	return OK;
}

//Free device to allow access by other processes
static int device_release(struct inode *inode, struct file *flip)
{
	Device_Open--;
	led = (short*) &sink;
	dipsw = (short*) &sink;
	button = (char*) &sink;
	iounmap((void*)virtual_base);
	module_put(THIS_MODULE);

	return OK;
}

//read from and write to device
long device_ioctl(struct file *flip, unsigned int ioctl_num, unsigned long ioctl_param)
{
	switch(ioctl_num)
	{
		case IOCTL_SET_LED:
			iowrite8((char)ioctl_param % 0xff, led);
			return OK;
		case IOCTL_GET_LED:
			return ioread8(led);
		case IOCTL_GET_DIPSW:
			return ioread8(dipsw);
		case IOCTL_GET_BUTTON:
			return ioread8(button);
		default:
			return -1;
	}
}

//Kernel module registration method
int init_module(void)
{
	Major = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
	if(Major != 0)
	{
		printk(KERN_ALERT "Registering %s chrdev failed with %d\n",DEVICE_NAME, Major);
		return Major;
	}
	printk(KERN_ALERT "Registering %s chrdev succeeded with Major=%d\n",DEVICE_NAME, MAJOR_NUM);
	
	return OK;
}

void cleanup_module(void)
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}
