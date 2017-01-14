# top makefile 

MAKE = make

all: limbo

.PHONY: limbo
limbo:
	$(MAKE) -C limbo

.PHONY: test
test: 
	$(MAKE) -C test

.PHONY: clean
clean:
	$(MAKE) clean -C limbo
	$(MAKE) clean -C test

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C limbo
	$(MAKE) extraclean -C test
