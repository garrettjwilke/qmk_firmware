#!/usr/bin/env bash

set -ex

make system76/launch_3:default

FIRMWARE="$(realpath .build/system76_launch_3_default.elf)"
cd openocd
sudo src/openocd \
    -f interface/cmsis-dap.cfg \
    -c "adapter speed 5000" \
    -f target/rp2040.cfg \
    -s tcl \
    -c "program ${FIRMWARE} verify reset exit"
