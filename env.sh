#!/bin/bash

export TOOLCHAIN=arm-none-eabi
export TOOLCHAIN_DIR=$HOME/x-tools/$TOOLCHAIN
export SYSROOT_DIR=$TOOLCHAIN_DIR/$TOOLCHAIN
export PATH=$TOOLCHAIN_DIR/bin:$PATH

export PRJ_DIR=$(pwd)
