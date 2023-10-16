#!/usr/bin/env bash

# will download pre-built binaries from:
# https://github.com/garrettjwilke/qmk_firmware/releases/latest

PROJECT_NAME=launch-midi-firmware
OFFLINE=false
ARGUMENT=$1
OS_CHECK=$(uname -a | awk '{print $1}')
case $OS_CHECK in
  Darwin) OS=mac;;
  Linux) OS=linux;;
  *) echo "OS not Linux or Mac. exiting"; exit;;
esac

install-deps() {
./util/qmk_install.sh
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
      source ~/.bashrc
    else
      echo ""
      echo "QMK not installed. install using your package manager or pip."
      echo ""
      exit
    fi
  elif [[ "$OS" == "mac" ]]
  then
    brew install qmk
  fi
fi
}


help-menu() {
cat << EOF

  | --------------------------------- |
  |                                   |
  |        Launch Keyboard MIDI       |
  |                                   |
  | --------------------------------- |

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

    3 - Download and flash MIDI Firmware to Launch Keyboard.

  If you are having issues, run the script with the --test flag:

    ./flash.sh --test

EOF
exit
}

qmk-check() {
# check for qmk
QMK_CHECK=$(which qmk)
if [[ "$QMK_CHECK" == "" ]]
then
clear

cat << EOF

  | --------------------------------- |
  |                                   |
  |        QMK is not installed       |
  |                                   |
  | --------------------------------- |

  Would you like to install the QMK tools? (y/n):
EOF
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
cat << EOF

  | --------------------------------- |
  |                                   |
  |            Run QMK Setup          |
  |                                   |
  | --------------------------------- |

  QMK is installed but the required tools are not installed.
  Would you like to install the QMK tools? (y/n):
EOF
read yn
case $yn in
  y|Y|yes|Yes|YES) qmk setup;;  
  n|N|no|No|NO) exit;;
esac
fi
}


dep-test() {
qmk-check

for i in wget sha256sum lsusb tar avrdude dfu-programmer dfu-util
do
  DEP=$(which $i)
  if [[ "$DEP" == "" ]]
  then
    echo ""
    echo "$i is not installed."
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
  echo ""
  echo "building piano firmware for $i"
  echo ""
  sleep 1
  make system76/${i}:midi_piano

  # launch_lite_ does not have enough keys for ghoti layout. skipping launch_lite_*
  if [[ "$i" != "launch_lite_1" ]]
  then
    echo ""
    echo "building ghoti firmware for $i"
    echo ""
    sleep 1
    make system76/${i}:midi_ghoti
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

echo ""
echo "all firmware built to $PROJECT_NAME directory"
echo "${PROJECT_NAME}.tar.gz created"
echo ""
exit
}

test-mode() {
dep-test
echo ""
echo "all tests passed."
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
elif [[ "$ARGUMENT" == "--test" ]]
then
  test-mode
elif [[ "$ARGUMENT" == "--build" ]]
then
  build-firmware
  exit
elif [[ "$ARGUMENT" == "--help" ]] || [[ "$ARGUMENT" == "-h" ]]
then
  help-menu
elif [[ "$ARGUMENT" == "--offline" ]]
then
  OFFLINE=true
elif [[ "$ARGUMENT" == "" ]]
then
  :
else
  echo ""
  echo "invalid flag. run with --help to see options"
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
  echo ""
  echo "Launch Keyboard not connected. run with --test"
  echo ""
  exit
fi

clear
cat << EOF

  | --------------------------------- |
  |                                   |
  |          Keyboard Detected        |
  |                                   |
  | --------------------------------- |

          Keyboard: $KEYBOARD

EOF

sleep 2

# ask user which version they want to flash
while true
do
clear

# launch_lite only has piano layout
if [[ "$KEYBOARD" == "launch_lite_1" ]]
then
  FIRMWARE=piano
  break
fi


cat << EOF

    Keyboard: $KEYBOARD

    | --------------------------------- |
    |                                   |
    |    Select a firmware to flash     |
    |                                   |
    | --------------------------------- |

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
    1) FIRMWARE=piano; break;;
    2) FIRMWARE=ghoti; break;;
    q|Q|quit|Quit|QUIT) exit;;
    *) echo "invalid input";;
  esac
done

download-firmware() {
  rm -rf ${PROJECT_NAME}*
  wget -q --show-progress https://github.com/garrettjwilke/qmk_firmware/releases/download/launch_midi/${PROJECT_NAME}.tar.gz
  tar -xzf ${PROJECT_NAME}.tar.gz
  rm ${PROJECT_NAME}.tar.gz
}
hash-check() {
while true
do
  if [[ "$OFFLINE" == "true" ]]
  then
    break
  fi
  # check firmware list sha256sum against newest version from git
  GIT_HASH=$(wget -q --show-progress -O - https://github.com/garrettjwilke/qmk_firmware/releases/download/launch_midi/${PROJECT_NAME}.list | sha256sum | awk '{print $1}')
  LOCAL_HASH=$(sha256sum ${PROJECT_NAME}.list | awk '{print $1}')

  echo "checking firmware hash."
  sleep 1

  if [[ "$LOCAL_HASH" == "$GIT_HASH" ]]
  then
    break
  else
    echo ""
    echo "hash does not match. downloading firmware."
    echo ""
    sleep 1
    clear
    echo ""
    echo "downloading firmware"
    echo ""
    download-firmware
  fi
done
}

# check if firmware directory exists
if ! [ -d $PROJECT_NAME ]
then
  download-firmware
  hash-check
fi

hash-check

FIRMWARE=$(cat ${PROJECT_NAME}.list | grep $KEYBOARD | grep $FIRMWARE | awk '{print $2}')
FIRMWARE_SHA256=$(cat ${PROJECT_NAME}.list | grep $KEYBOARD | grep $FIRMWARE | awk '{print $1}')

if [[ "$FIRMWARE" == "" ]]
then
  echo ""
  echo "ERROR - firmware select failed. exiting"
  echo ""
  exit
fi


# check for firmware and download if not found
# also check hash of firmware and download if incorrect
while true
do
  if ! [ -f ${PROJECT_NAME}/$FIRMWARE ]
  then
    if [[ "$OFFLINE" == "true" ]]
    then
      echo ""
      echo "firmware file does not exist. Offline Mode enabled. exiting"
      echo ""
      exit
    fi
    echo ""
    echo "Downloading Launch MIDI firmware files..."
    echo ""
    download-firmware
    hash-check
  fi

  # check sha256sum of downloaded firmware before flashing

  SHA256_TEST=$(sha256sum ${PROJECT_NAME}/$FIRMWARE | awk '{print $1}')
  if [[ "$SHA256_TEST" != $FIRMWARE_SHA256 ]]
  then
    if [[ "$OFFLINE" == "true" ]]
    then
      echo ""
      echo "sha256sum hash check failed. Offline Mode enabled. exiting"
      echo ""
      exit
    fi
    echo "firmware hash does not match. deleting and downloading firmware again."
    download-firmware
    hash-check
    sleep 2
  else
    break
  fi
done

# instruct user how to put keyboard into DFU
clear
cat << EOF

  Keyboard: $KEYBOARD

  | --------------------------------- |
  |                                   |
  |      Put Launch into DFU Mode     |
  |                                   |
  | --------------------------------- |

  This will not start flashing until the Launch is in DFU Mode.
  Follow the instructions below to put your Launch Keyboard in DFU mode.

    1. Unplug Launch
    2. Press and hold the ESC key
    3. Plug in Launch while holding the ESC key
    4. Release the ESC key when the keyboard is recognized (About 2-3 seconds after plugging in)

EOF

while true
do
  # comment the break line below to enable DFU check
  break
  if [[ "$OS" == "linux" ]]
  then
    DFU_CHECK=$(lsusb | grep "atmega32u4")
  elif [[ "$OS" == "mac" ]]
  then
    DFU_CHECK=$(system_profiler SPUSBDataType 2 | grep "Atmel Corporation")
  fi
  
  if [[ "$DFU_CHECK" != "" ]]
  then
  clear
cat << EOF

  | --------------------------------- |
  |                                   |
  |          DFU MODE ENABLED         |
  |                                   |
  |        RELEASE THE ESC KEY        |
  |                                   |
  |    DO NOT UNPLUG YOUR KEYBOARD!   |
  |                                   |
  | --------------------------------- |

EOF
    sleep 2
    break
  fi
  sleep 1
done

# final firmware check before flashing keyboard
if [[ "$FIRMWARE" == "" ]]
then
  echo ""
  echo "ERROR - MIDI layout not found. Exiting."
  echo ""
  exit
fi

# flash firmware
qmk flash ${PROJECT_NAME}/$FIRMWARE
