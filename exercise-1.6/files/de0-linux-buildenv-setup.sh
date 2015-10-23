#! /bin/bash
PROJECT_DIR="${PWD}"
sudo apt-get install  gcc-4.8-multilib-arm-linux-gnueabihf g++ g++-arm-linux-gnueabihf git gcc  gcc-arm-linux-gnueabihf  gcc-multilib g++-multilib gawk wget git-core diffstat unzip texinfo build-essential chrpath socat libsdl1.2-dev xterm
mkdir ~/git_de0
cd ~/git_de0; git clone git://support.criticallink.com/home/git/linux-socfpga.git
cd ~/git_de0/linux-socfpga; git checkout socfpga-3.13
cp "${PROJECT_DIR}"/Makefile.de0 ~/git_de0/linux-socfpga/Makefile
tar xvf "${PROJECT_DIR}"/socal.tar -C /usr/include 
cd ~/git_de0/linux-socfpga; make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- defconfig socfpga_defconfig

ORIGINAL=CONFIG_LOCALVERSION_AUTO=y
REPLACE=CONFIG_LOCALVERSION_AUTO=n
for word in $(fgrep -l $ORIGINAL ~/git_de0/linux-socfpga/.config)
do
	ex $word <<EOF
	:%s/$ORIGINAL/$REPLACE/g
	:wq
EOF
done

cd ~/git_de0/linux-socfpga; make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- LOADADDR=0x8000 LOCALVERSION= modules; sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- LOADADDR=0x8000 LOCALVERSION= modules_install
