# Makefile for the entire project

all:
	( ($(MAKE) clean -C src); ($(MAKE) clean -C test/src); (($(MAKE) -C src) && (($(MAKE) -C test/src))); ./test/src/test_all.out)

clean:
	(($(MAKE) clean -C src) && (($(MAKE) clean -C test/src)))

.PHONY: all clean
