#!/usr/bin/env bash

set -ex

make system76/virgo_keyboard_test_1:default

FIRMWARE="$(realpath .build/system76_virgo_keyboard_test_1_default.elf)"
cd openocd
sudo src/openocd \
    -f interface/cmsis-dap.cfg \
    -c "adapter speed 5000" \
    -f target/rp2040.cfg \
    -s tcl \
    -c "program ${FIRMWARE} verify reset exit"
