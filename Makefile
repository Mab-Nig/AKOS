#####################################################################
# @author: dt
# @email : tien.ta.eswe@gmail.com
# @date  : 25/03/2026
#####################################################################


BOARD		?= stm32l151xx

TARGET 		= ak-os-$(BOARD)
BUILD_DIR 	= build/$(BOARD)

PREFIX 		= arm-none-eabi-
CC 			= $(PREFIX)gcc
CXX			= $(PREFIX)g++
AS 			= $(PREFIX)gcc -x assembler-with-cpp
SZ 			= $(PREFIX)size
LD			= $(PREFIX)ld
OBJCOPY 	= $(PREFIX)objcopy
OBJDUMP		= $(PREFIX)objdump

CPU			=
DEFINES		=
SRCS		=
INCLUDE		=
ASM_SRCS	=
LDSCRIPT	=
OOCD_IF		=
OOCD_TARGET =

include test/$(BOARD)/Makefile.mk
include ak/Makefile.mk
include driv/Makefile.mk
include ext/Makefile.mk
include port/Makefile.mk

GENERAL_FLAGS = -O0 -g3 						\
				-fdata-sections 				\
				-ffunction-sections 			\
				-Wall -Wshadow -Wpointer-arith	\
				-MMD -MP						\
				--specs=nano.specs  			\
				--specs=nosys.specs				\
				-fsingle-precision-constant

CFLAGS  = $(CPU) $(DEFINES) $(INCLUDE) $(GENERAL_FLAGS) -std=c99 -MF"$(@:%.o=%.d)"
CXXFLAGS = $(CPU) $(DEFINES) $(INCLUDE) $(GENERAL_FLAGS) -std=c++11 -MF"$(@:%.o=%.d)"

LDFLAGS = $(CPU)									\
		 -T$(LDSCRIPT)								\
		 -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref	\
		 -Wl,--gc-sections

OBJS	 = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
ASM_OBJS = $(addprefix $(BUILD_DIR)/, $(ASM_SRCS:.s=.o))

.PHONY: prebuild all clean print_size flash

all: prebuild $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin print_size

prebuild:
	@mkdir -p $(dir $@)

$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(ASM_OBJS)
	@echo "[LINK] $@"
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	@echo "[BIN] $@"
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.o: %.c
	@echo "[CC] $<"
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo "[CXX] $<"
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s
	@echo "[AS] $<"
	$(AS) -c $(CFLAGS) $< -o $@

print_size: $(BUILD_DIR)/$(TARGET).elf
	@echo ""
	$(SZ) $<

clean:
	@echo "[CLEAN] Remove directory: $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

flash: all
	@echo "[FLASH] Loading code by OpenOCD ..."
	openocd -f interface/$(OOCD_IF)-f target/$(OOCD_TARGET) -c "program $(BUILD_DIR)/$(TARGET).elf verify reset exit"

-include $(wildcard $(BUILD_DIR)/**/*.d)
