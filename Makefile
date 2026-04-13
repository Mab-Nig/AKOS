### Import env.sh first! ###

AS	= $(TOOLCHAIN)-gcc -x assembler-with-cpp
CC	= $(TOOLCHAIN)-gcc -std=c99 --sysroot=$(SYSROOT_DIR)
CXX	= $(TOOLCHAIN)-g++ -std=c++17 --sysroot=$(SYSROOT_DIR)

TARGET		=
ARCH_FLAGS	=
DEFS		=
INCS		=
SRCS		=
LDSCRIPT	=

include ak/Makefile.mk
include port/Makefile.mk
include ext/Makefile.mk
include test/Makefile.mk
include docs/Makefile.mk

INC_FLAGS	= $(addprefix -I,$(INCS))
DEF_FLAGS	= $(addprefix -D,$(DEFS))
OBJS =\
	$(patsubst %.c,%.o,$(filter %.c,$(SRCS)))\
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))\
DEPS 		= $(OBJS:.o=.d)

CPPFLAGS = -MMD -MP $(DEF_FLAGS) $(INC_FLAGS)
CFLAGS =\
	$(ARCH_FLAGS)\
	-flto\
	-ffunction-sections -fdata-sections\
	-Wall -Werror\
	-Wshadow\
	-Wcast-qual\
	-Wpointer-arith\
	-Wwrite-strings\
	-Wno-stringop-overflow\
	-Wstrict-prototypes\
	-save-temps\
	-fverbose-asm\
CXXFLAGS =\
	$(CFLAGS)\
	-fno-exceptions -fno-rtti -fno-unwind-tables -fomit-frame-pointer\
LDFLAGS =\
	-T$(LDSCRIPT)\
	--specs=nosys.specs\
	--specs=nano.specs\
	-static\
	-flto\
	-Wl,--gc-sections\

.PHONY: prebuild $(TARGET)_dbg $(TARGET)_rel clean

test_dbg: CFLAGS += -g
test_dbg: CXXFLAGS += -g
test_dbg: prebuild $(OBJS)
	@echo "Building target $@."
	$(CXX) $(OBJS) -o build/dbg/$(TARGET) $(LDFLAGS)

test_rel: CFLAGS += -DNDEBUG
test_rel: CXXFLAGS += -DNDEBUG
test_rel: prebuild $(OBJS)
	@echo "Building target $@."
	$(CXX) $(OBJS) -o build/rel/$(TARGET) $(LDFLAGS)

prebuild:
	@mkdir build/

build/%.o: %.c
	@mkdir -p "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/%.o: %.cpp
	@mkdir -p "$(dir $@)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/%.o: %.s
	@mkdir -p "$(dir $@)"
	$(AS) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf build/

-include $(DEPS)
