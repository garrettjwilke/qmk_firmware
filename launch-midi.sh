#!/usr/bin/env bash

# will download pre-built binaries from:
# https://github.com/garrettjwilke/qmk_firmware/releases/latest

PROJECT_NAME=launch-midi-firmware
ARGUMENT=$1

message-box() {
MESSAGE=$1
cat << EOF
  ---------------------------------

    $MESSAGE

  ---------------------------------

EOF
}

OS_CHECK=$(uname -a | awk '{print $1}')
case $OS_CHECK in
  Darwin) OS=mac;;
  Linux) OS=linux;;
  *) message-box "This script requires Linux"; exit;;
esac

install-deps() {
BASHRC_CHECK=$(cat ~/.bashrc | grep "\.local\/bin")
./util/qmk_install.sh
git submodule init
git submodule update
QMK_CHECK=$(which qmk)
if [[ "$QMK_CHECK" == "" ]]
then
  if [[ "$OS" == "linux" ]]
  then
    DISTRO_CHECK=$(cat /etc/os-release | grep "^NAME" | sed 's/NAME\=//g' | tr -d \")
    if [[ "$DISTRO_CHECK" == "Arch Linux" ]] || [[ "$DISTRO_CHECK" == "Manjaro Linux" ]]
    then
      sudo pacman -Syy
      sudo pacman -S qmk usbutils wget --noconfirm
    elif [[ "$DISTRO_CHECK" == "Ubuntu" ]] || [[ "$DISTRO_CHECK" == "Pop!_OS" ]]
    then
      python3 -m pip install qmk
      PATH=$PATH:$HOME/.local/bin
      echo "export PATH=\$PATH:\$HOME/.local/bin" >> ~/.bashrc
    else
      message-box "QMK not installed."
      echo "Install QMK using pip or your package manager."
      echo ""
      exit
    fi
  elif [[ "$OS" == "mac" ]]
  then
    echo "qmk not installed"
    brew install qmk
  fi
fi
clear
message-box "All tools installed"
sleep 2
if [[ "$OS" == "linux" ]]
then
  exec bash ./launch-midi.sh
fi
}


help-menu() {
message-box "Launch Keyboard MIDI Firmware"
cat << EOF
  System76 Launch Keyboard MIDI Firmware

  What this script does:

    1 - Identify which Launch Keyboard you have connected.

    2 - Ask you which firmware you would like to flash.
        There are 2 firmwares: Piano and Ghoti
          Piano
            * Keys are set up like a piano, with sharps/flats above your natural keys.
            * There are 2 rows of 2 octaves each.
            * Has 32 Pad Drum Layer.
          Ghoti
            * Keys are set up in vertical columns. There are 5 notes per column.
            * Each column creates a perfect 4th of the adjacent column to the right.
            * Has 32 Pad Drum Layer.

    3 - Build and ask to flash MIDI Firmware to Launch Keyboard.

EOF
exit
}

qmk-check() {
PATH=$PATH:$HOME/.local/bin
# check for qmk
QMK_CHECK=$(which qmk)
if [[ "$QMK_CHECK" == "" ]]
then
clear
message-box "QMK is not installed."
echo "Would you like to install QMK? (y/n):"
echo ""
read yn
case $yn in
  y|Y|yes|Yes|YES) install-deps;;
  n|N|no|No|NO) exit;;
esac
fi

# check if qmk setup was ran
QMK_SETUP=$(qmk -h | grep flash)
if [[ "$QMK_SETUP" == "" ]]
then
clear
message-box "Run qmk setup"
echo "QMK is installed but the required tools are not installed."
echo "Would you like to install the QMK tools? (y/n):"
read yn
case $yn in
  y|Y|yes|Yes|YES) qmk setup;;
  n|N|no|No|NO) exit;;
esac
fi
}


dep-test() {
qmk-check

for i in wget sha256sum tar avrdude dfu-programmer dfu-util
do
  DEP=$(which $i)
  if [[ "$DEP" == "" ]]
  then
    message-box "$i is not installed."
    if [[ "$i" == "avrdude" ]] || [[ "$i" == "dfu-programmer" ]] || [[ "$i" == "dfu-util" ]]
    then
      echo "$i can be installed by running:"
      echo "    qmk setup"
      echo ""
    fi
    exit
  fi
done
}

build-firmware() {
qmk-check
KEYBOARD_LIST="launch_1 launch_2 launch_3 launch_lite_1 launch_heavy_1 launch_heavy_3"

make clean

for i in $KEYBOARD_LIST
do
  message-box "building piano firmware for $i"
  echo ""
  sleep 1
  make system76/${i}:midi_piano
  if [ $? -gt 0 ]
  then
    message-box "Error building MIDI Firmware."
    echo "Keyboard: $i"
    echo "Firmware: midi_piano"
    echo ""
    exit
  fi
  # launch_lite_ does not have enough keys for ghoti layout. skipping launch_lite_*
  if [[ "$i" != "launch_lite_1" ]]
  then
    echo ""
    echo "building ghoti firmware for $i"
    echo ""
    sleep 1
    make system76/${i}:midi_ghoti
    if [ $? -gt 0 ]
    then
      message-box "Error building MIDI Firmware."
      echo "Keyboard: $i"
      echo "Firmware: midi_piano"
      echo ""
      exit
    fi
  fi
done


if [ -d $PROJECT_NAME ]
then
  rm -rf $PROJECT_NAME*
fi

mkdir $PROJECT_NAME

mv system76_launch* ${PROJECT_NAME}/

pushd $PROJECT_NAME
sha256sum system76_launch_* > ../${PROJECT_NAME}.list
popd

tar -czf ${PROJECT_NAME}.tar.gz $PROJECT_NAME ${PROJECT_NAME}.list

message-box "Firmware build complete"
echo "all firmware built to $PROJECT_NAME directory"
echo "${PROJECT_NAME}.tar.gz created"
echo ""
exit
}


if [[ "$ARGUMENT" == "--git" ]]
then
  echo ""
  echo "Push to git? (y/n)"
  echo ""
  read GIT
  case $GIT in
    Y|y|Yes|YES|yes) git add .; git commit -m "launch_midi"; git push; echo ""; echo "pushed to git"; echo ""; exit;;
    N|n|No|NO|no) echo ""; echo "not pushing to git"; echo ""; exit;;
    *) echo ""; echo "invalid input. exiting"; echo ""; exit;;
  esac
elif [[ "$ARGUMENT" == "--build" ]]
then
  build-firmware
  exit
elif [[ "$ARGUMENT" == "--help" ]] || [[ "$ARGUMENT" == "-h" ]]
then
  help-menu
elif [[ "$ARGUMENT" == "" ]]
then
  :
else
  message-box "Invalid flag: $ARGUMENT"
  echo "Run with --help to see options"
  echo ""
  exit
fi


# set empty vars
FIRMWARE=""

dep-test

# find which Launch Keyboard is connected
if [[ "$OS" == "linux" ]]
then
  KEYBOARD=$(lsusb | grep "(launch_*" | awk '{print $NF}' | tr -d "():")
elif [[ "$OS" == "mac" ]]
then
  KEYBOARD=$(system_profiler SPUSBDataType | grep "(launch_*" | awk '{print $NF}' | tr -d "():")
fi

if [[ "$KEYBOARD" == "" ]]
then
  message-box "Launch Keyboard not connected."
  exit
fi

clear
message-box "Keyboard Detected - $KEYBOARD"
sleep 2

# ask user which version they want to flash
while true
do
clear

# launch_lite only has piano layout
if [[ "$KEYBOARD" == "launch_lite_1" ]]
then
  FIRMWARE=midi_piano
  break
fi

message-box "Select a firmware to flash"
cat << EOF
    Keyboard: $KEYBOARD

    [ 1 ] Piano with 32 Drum Pads
          - Keys are arranged like a piano
          - 32 Drum Pad Layer

    [ 2 ] Ghoti with 32 Drum Pads
          - Keys are arranged chromatically in vertical columns
            - Each column has 5 half-steps
            - Adjacent notes are all Perfect Fourths
            - You can travel the Circle of Fifths by shifting a chord left or right
            - Steep learning curve.
          - 32 Drum Pad Layer

    [ q ] Quit

     Press 1 or 2 (q to quit):

EOF

  read LAYOUT
  case $LAYOUT in
    1) FIRMWARE=midi_piano; break;;
    2) FIRMWARE=midi_ghoti; break;;
    q|Q|quit|Quit|QUIT) exit;;
    *) echo "invalid input";;
  esac
done


if [[ "$FIRMWARE" == "" ]]
then
  message-box "Error. Firmware select failed."
  exit
fi


# build firmware

make clean
make system76/${KEYBOARD}:${FIRMWARE}

if [ $? -gt 0 ]
then
  message-box "Build failed"
  exit
fi

# instruct user how to put keyboard into DFU
clear
message-box "Put Launch into bootloader mode"
cat << EOF
  Keyboard: $KEYBOARD
  Firmware: $FIRMWARE

  This will not start flashing until the Launch is in bootloader mode.
  Follow the instructions below to put your Launch Keyboard in bootloader mode.

    1. Unplug Launch
    2. Press and hold the ESC key
    3. Plug in Launch while holding the ESC key
    4. Release the ESC key when the keyboard is recognized (About 2-3 seconds after plugging in)

  The script will verify the firmware and then
  attempt to flash once the keyboard is in bootloader mode.

  Press ENTER to continue

EOF

read INPUT

make system76/${KEYBOARD}:${FIRMWARE}:dfu

if [ $? -gt 0 ]
then
  message-box "Flash failed"
else
  message-box "Flashed MIDI Firmware to $KEYBOARD"
fi
exit
