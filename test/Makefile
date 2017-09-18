all: parsers 

.PHONY: parsers 

algorithms:
	$(MAKE) -C algorithms

geometry:
	$(MAKE) -C geometry

parsers:
	$(MAKE) -C parsers

programoptions:
	$(MAKE) -C programoptions

solvers:
	$(MAKE) -C solvers

string:
	$(MAKE) -C string

.PHONY: clean
clean:
	$(MAKE) clean -C parsers

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C parsers
