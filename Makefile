all: main test

main:
	$(MAKE) -C src/main

test:
	$(MAKE) -C src/test

