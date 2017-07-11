export CROSS_COMPILE=/home/hardik/Documents/ndk/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-
make clean && make mrproper
make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILE gionee6753_65u_m0_defconfig
make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILE -j2 

