ifndef PLATFORM
    $(error [TOOLCHAIN] PLATFORM must be either 'host' or 'target'.)
else
    $(info [TOOLCHAIN] PLATFORM=$(PLATFORM).)
endif

PLATFORM_LCASE = $(shell echo $(PLATFORM) | tr '[:upper:]' '[:lower:]')

AS = $(TOOLCHAIN)-gcc -x assembler-with-cpp

ifeq ($(PLATFORM_LCASE),target)
    TOOLCHAIN = arm-none-eabi
    CC      = $(TOOLCHAIN)-gcc -std=c99 --sysroot=$(SYSROOT_DIR)
    CXX     = $(TOOLCHAIN)-g++ -std=c++17 --sysroot=$(SYSROOT_DIR)
    OBJCOPY = $(TOOLCHAIN)-objcopy
else
    CC      = gcc -std=c99
    CXX     = g++ -std=c++17
    OBJCOPY = objcopy
endif
