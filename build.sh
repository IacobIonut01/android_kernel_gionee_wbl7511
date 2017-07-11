END_COLOR='\033[1;34m'
clear
echo Creating Environment for Compiling Kernel...
export CROSS_COMPILE=toolchains/bin/aarch64-linux-gnu-
sudo apt-get install libncurses5-dev
sudo apt-get install git-core gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 libgl1-mesa-dev g++-multilib tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386
export USE_CCACHE=1
clear
echo Environment sucessfully created.
echo
sleep 1
echo Cleaning Build Folder
make clean && make mrproper
echo Fixing incomming build errors
cd tools
mkdir tools
cd ..
sleep 1
clear
echo Starting Compiling Kernel....
make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILE gionee6753_65u_m0_defconfig
make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILE -j6
