clear
echo Creating Environment for Compiling Kernel...
chmod --recursive 777 *
export CROSS_COMPILE=toolchain/bin/aarch64-linux-android-
sudo apt-get install libncurses5-dev
sudo apt-get install git-core gnupg flex bison gperf build-essential zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 libgl1-mesa-dev g++-multilib tofrodos python-markdown libxml2-utils xsltproc zlib1g-dev:i386
export USE_CCACHE=1
export ARCH=arm64
export SUBARCH=arm64
make gionee6753_65u_m0_defconfig
clear
echo Environment sucessfully created.
echo
sleep 1
cd tools
mkdir tools
cd ..
sleep 1
clear
echo Starting Compiling Kernel....
make -j30
