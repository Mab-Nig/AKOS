ifndef TEST
	$(error [TEST] TEST is not defined.)
endif
TEST_LCASE = $(shell echo $(TEST) | tr '[:upper:]' '[:lower:]')

TESTS = list

.PHONY: prebuild all $(TESTS)

$(TEST_LCASE): prebuild
	make -C $(TEST_LCASE)

all: $(TESTS)

prebuild:
	. ./setup.sh
