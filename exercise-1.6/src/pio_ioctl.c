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

//Required function address structure
struct file_operations fops = {
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
	.release = device_release
};

//Open device for i/o operations
static int device_open(struct inode *inode, struct file *flip)
{
	
	return OK;
}

//Free device to allow access by other processes
static int device_release(struct inode *inode, struct file *flip)
{
	
	return OK;
}

//read from and write to device
long device_ioctl(struct file *flip, unsigned int ioctl_num, unsigned long ioctl_param)
{
	switch(ioctl_num)
	{
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