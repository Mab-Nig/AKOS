ifndef SRCS
	$(error [VARS] SRCS is not defined.)
endif

OBJS_C   = $(SRCS:.c=.o)
OBJS_CPP = $(OBJS_C:.cpp=.o)
OBJS_S   = $(OBJS_CPP:.s=.o)

OBJS = $(patsubst $(PRJ_DIR)/%.o,$(PRJ_DIR)/build/%.o,$(OBJS_S))
DEPS = $(OBJS:.o=.d)
