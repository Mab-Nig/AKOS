MODE       ?= debug
MODE_LCASE = $(shell echo $(MODE) | tr '[:upper:]' '[:lower:]')

$(info [FLAGS] MODE is either 'debug' or 'release'. MODE=debug by default.)

ifndef INCS
    $(error [FLAGS] INCS is not defined.)
endif

COMMON_FLAGS =\
	-ffunction-sections -fdata-sections\
	-Wall -Werror\
	-Wshadow\
	-Wcast-qual\
	-Wpointer-arith\
	-Wwrite-strings\
	-Wno-stringop-overflow\
	-Wstrict-prototypes\
	-save-temps\
	-fverbose-asm
INC_FLAGS = $(addprefix -I,$(INCS))
DEF_FLAGS = $(addprefix -D,$(DEFS))

ifdef LDSCRIPT
    LDSCRIPT_FLAG = -T$(LDSCRIPT)
    $(info [FLAGS] LDSCRIPT=$(LDSCRIPT).)
else
    $(info [FLAGS] Specify linker script through LDSCRIPT.)
endif

ifeq ($(MODE_LCASE),debug)
	OPT_FLAGS += -O0 -g3
else
	OPT_FLAGS += -Os -flto
	DEF_FLAGS += -DNDEBUG
endif

CPPFLAGS = -MMD -MP $(DEF_FLAGS) $(INC_FLAGS)
CFLAGS   = $(ARCH_FLAGS) $(OPT_FLAGS) $(COMMON_FLAGS)
CXXFLAGS =\
	$(CFLAGS)\
	-fno-exceptions -fno-rtti -fno-unwind-tables -fomit-frame-pointer
LDFLAGS =\
	$(LDSCRIPT_FLAG) $(ARCH_FLAGS) $(SPECS_FLAGS)\
	-static -flto -Wl,--gc-sections
