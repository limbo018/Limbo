all: def lef 
.PHONY: def lef

bookshelf:
	$(MAKE) -C bookshelf/bison

def:
	$(MAKE) -C def/adapt

ebeam:
	$(MAKE) -C ebeam/bison

gdf:
	$(MAKE) -C gdf/bison

gdsii:
	$(MAKE) -C gdsii/stream
	$(MAKE) -C gdsii/gdsdb

lef:
	$(MAKE) -C lef/adapt

lp:
	$(MAKE) -C lp/bison

tf:

verilog:
	$(MAKE) -C verilog/bison

.PHONY: install
install:
	$(MAKE) install -C def/adapt
	$(MAKE) install -C lef/adapt

.PHONY: clean
clean:
	$(MAKE) clean -C def/adapt
	$(MAKE) clean -C lef/adapt

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C def/adapt
	$(MAKE) extraclean -C lef/adapt
