export SHELL = /bin/bash

.PHONY: clean test

test:
	make -wi -C test

clean:
	@rm -rf build/
