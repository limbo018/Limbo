# top makefile 

MAKE = make

# list of components 
PARSERS = limbo/parsers
SOLVERS = limbo/solvers

RESRCS = \
		 $(PARSERS)/def/bison \
		 $(PARSERS)/lef/bison \
		 $(PARSERS)/ebeam/bison \
		 $(PARSERS)/lp/bison \
		 $(PARSERS)/gdsii/stream \
		 $(SOLVERS)/lpmcf

.PHONY: build 

build: 
	mkdir -p lib 
	$(MAKE) -C $(PARSERS)/def/bison
	$(MAKE) all -C $(PARSERS)/lef/bison
	$(MAKE) -C $(PARSERS)/ebeam/bison
	$(MAKE) -C $(PARSERS)/lp/bison
	$(MAKE) -C $(PARSERS)/gdsii/stream
	
install:
	mkdir -p lib 
	$(MAKE) install -C $(PARSERS)/def/bison
	$(MAKE) install -C $(PARSERS)/lef/bison
	$(MAKE) install -C $(PARSERS)/ebeam/bison
	$(MAKE) install -C $(PARSERS)/lp/bison
	$(MAKE) install -C $(PARSERS)/gdsii/stream

clean:
	$(MAKE) extraclean -C $(PARSERS)/def/bison
	$(MAKE) extraclean -C $(PARSERS)/lef/bison
	$(MAKE) extraclean -C $(PARSERS)/ebeam/bison
	$(MAKE) extraclean -C $(PARSERS)/lp/bison
	$(MAKE) extraclean -C $(PARSERS)/gdsii/stream
