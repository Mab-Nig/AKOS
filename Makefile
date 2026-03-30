CC	= $(TOOLCHAIN)-gcc -std=c99 --sysroot=$(SYSROOT_DIR)
CXX	= $(TOOLCHAIN)-g++ -std=c++17 --sysroot=$(SYSROOT_DIR)

ARCH_FLAGS	=
INC_FLAGS	=
SRCS		=
LDSCRIPT	=

include $(OS_DIR)/Makefile.mk
include $(PORT_DIR)/Makefile.mk
include $(EXT_DIR)/Makefile.mk
include $(TEST_DIR)/Makefile.mk
include $(DOCS_DIR)/Makefile.mk

OBJS	= \
	$(patsubst %.c,%.o,$(filter %.c,$(SRCS))) \
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS))) \
DEPS	= $(OBJS:.o=.d)

CPPFLAGS = -MMD -MP $(INC_FLAGS)
CFLAGS = \
	$(ARCH_FLAGS) \
	-Os \
	-flto \
	-ffunction-sections -fdata-sections \
	-Wall -Werror \
	-Wshadow \
	-Wcast-qual \
	-Wpointer-arith \
	-Wwrite-strings \
	-Wno-stringop-overflow \
	-Wstrict-prototypes \
	-save-temps \
	-fverbose-asm \
CXXFLAGS = \
	$(CFLAGS) \
	-fno-exceptions -fno-rtti -fno-unwind-tables -fomit-frame-pointer \
LDFLAGS = \
	-T$(LDSCRIPT) \
	--specs=nosys.specs \
	--specs=nano.specs \
	-static \
	-flto \
	-Wl,--gc-sections \

.PHONY: prebuild test_dbg test_rel clean

prebuild:
	mkdir build/

test_dbg: CFLAGS += -g
test_dbg: prebuild $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD_DIR)/debug/test $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/

-include $(DEPS)
