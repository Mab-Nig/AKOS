CC	= $(TOOLCHAIN)-gcc -std=c99 --sysroot=$(SYSROOT_DIR)
CXX	= $(TOOLCHAIN)-g++ -std=c++17 --sysroot=$(SYSROOT_DIR)

ARCH_FLAGS	=
INCS		=
SRCS		=
LDSCRIPT	=

include ak/Makefile.mk
# include port/Makefile.mk
# include ext/Makefile.mk
include test/Makefile.mk
# include docs/Makefile.mk

INC_FLAGS	= $(addprefix -I,$(INCS))
OBJS		=										\
	$(patsubst %.c,%.o,$(filter %.c,$(SRCS)))		\
	$(patsubst %.cpp,%.o,$(filter %.cpp,$(SRCS)))
DEPS		= $(OBJS:.o=.d)

CPPFLAGS = -MMD -MP $(INC_FLAGS)
CFLAGS =								\
	$(ARCH_FLAGS)						\
	-flto								\
	-ffunction-sections -fdata-sections	\
	-Wall -Werror						\
	-Wshadow							\
	-Wcast-qual							\
	-Winline							\
	-Wpointer-arith						\
	-Wwrite-strings						\
	-Wno-stringop-overflow				\
	-Wstrict-prototypes					\
	-save-temps							\
	-fverbose-asm
CXXFLAGS = -fno-exceptions -fno-rtti -fno-unwind-tables -fomit-frame-pointer
LDFLAGS = 				\
	-T$(LDSCRIPT) 		\
	--specs=nosys.specs	\
	--specs=nano.specs 	\
	-static				\
	-flto				\
	-Wl,--gc-sections

.PHONY: prebuild test_dbg test_rel clean

test_rel: CFLAGS += -Os
test_rel: prebuild $(OBJS)
	$(CXX) $(OBJS) -o build/release/test $(LDFLAGS)

test_dbg: CFLAGS += -Og -g
test_dbg: prebuild $(OBJS)
	$(CXX) $(OBJS) -o build/debug/test $(LDFLAGS)

prebuild:
	@mkdir build/

build/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

build/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf build/

-include $(DEPS)
