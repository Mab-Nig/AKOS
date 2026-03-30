#!/bin/bash

export TOOLCHAIN=arm-none-eabi
export TOOLCHAIN_DIR=$HOME/x-tools/$TOOLCHAIN
export SYSROOT_DIR=$TOOLCHAIN_DIR/$TOOLCHAIN
export PATH=$TOOLCHAIN_DIR/bin:$PATH

export OS_DIR=os
export PORT_DIR=port
export EXT_DIR=ext
export TEST_DIR=test
export DOCS_DIR=docs
export BUILD_DIR=build
