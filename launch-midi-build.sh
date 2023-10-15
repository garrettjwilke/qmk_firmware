#!/usr/bin/env bash

DATE_NOW=$(date +%s)

BUILD_NAME=launch-midi-firmware

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


if [ -d $BUILD_NAME ]
then
  rm -rf $BUILD_NAME*
fi

mkdir $BUILD_NAME

mv system76_launch* ${BUILD_NAME}/

echo "Build Date: $DATE_NOW" > ${BUILD_NAME}.list

echo "" >> ${BUILD_NAME}.list
pushd $BUILD_NAME
sha256sum system76_launch_* >> ../${BUILD_NAME}.list
popd

tar -czf ${BUILD_NAME}.tar.gz $BUILD_NAME ${BUILD_NAME}.list

echo ""
echo "all firmware built to $BUILD_NAME directory"
echo "${BUILD_NAME}.tar.gz created"
echo "" 
