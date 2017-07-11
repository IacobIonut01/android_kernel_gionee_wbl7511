Download NDK and extract it and rename it to ndk

go to kernel root source

open terminal and type

export CROSS_COMPILE=/home/hardik/Documents/ndk/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-


make clean && make mrproper

export ARCH=arm64

make gionee6753_65u_m0_defconfig

make ARCH=arm64
