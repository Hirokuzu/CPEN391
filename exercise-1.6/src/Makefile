#! /bin/bash

obj-m +=pio_ioctl.o

EXECDIR= /lib/modules/3.13.0-00298-g3c7cbb9-dirty/build
ARM_CC= /usr/bin/arm-linux-gnueabihf-gcc
INCLUDE_DIRS= -I./ -I$(EXECDIR)/include

all: test libpio_ioctl_api.so

test: test.c
	$(ARM_CC) test.c -o test -lpio_ioctl_api

libpio_ioctl_api.so: pio_ioctl_api.o
	$(ARM_CC) -shared -o libpio_ioctl_api.so pio_ioctl_api.o

pio_ioctl_api.o:
	$(ARM_CC) -c -fPIC pio_ioctl_api.c $(INCLUDE_DIRS)

pio_ioctl.ko:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(EXECDIR) M=$PWD modules

clean:
	\rm *.o *~ test
