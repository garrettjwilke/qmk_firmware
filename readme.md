# System76 QMK MIDI Firmware for Launch_1 Keyboards

Custom MIDI support for System76 Launch Keyboards.

## Installation
1) Clone the QMK Firmware Repo and update the submodules:

```
git clone https://github.com/garrettjwilke/qmk_firmware
cd qmk_firmware
git submodules init
git submodules update
```

2) Install QMK and the required dependencies:

```
./util/qmk_install.sh
```

3) Build Launch MIDI firmware:
```
./build.sh
```

This will produce all MIDI firmware and output the sha256sum of each firmware to a file called `firmware.list`.
