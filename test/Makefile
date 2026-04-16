ifndef TEST
	$(error [TEST] TEST is not defined.)
endif
TEST_LCASE = $(shell echo $(TEST) | tr '[:upper:]' '[:lower:]')
TEST       = $(TEST_LCASE)

TESTS = list

.PHONY: prebuild all $(TESTS)

$(TEST): prebuild
	make -wi -C $(TEST)

all: $(TESTS)

prebuild:
	. ./setup.sh
