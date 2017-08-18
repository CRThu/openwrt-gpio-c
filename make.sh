export STAGING_DIR=/home/wooya/Downloads/openwrt/staging_dir/toolchain-mipsel_24kec+dsp_gcc-4.8-linaro_uClibc-0.9.33.2
export PATH=$PATH:$STAGING_DIR/bin
mipsel-openwrt-linux-gcc gpio-c/gpio.cpp gpio-c/main.cpp -o gpio-c/gpio-c
