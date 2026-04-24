ifndef TEST
    $(error [TEST] TEST is not defined.)
else
    $(info [TEST] TEST=$(TEST).)
endif
TEST_LCASE = $(shell echo $(TEST) | tr '[:upper:]' '[:lower:]')

TESTS = list prio

.PHONY: prebuild all $(TESTS)

$(TEST_LCASE): prebuild
	make -C $(TEST_LCASE)

all: $(TESTS)

prebuild:
	. ./setup.sh
