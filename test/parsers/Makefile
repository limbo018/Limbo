all: def lef
.PHONY: def lef

bookshelf:
	$(MAKE) -C bookshelf

def:
	$(MAKE) -C def

ebeam:
	$(MAKE) -C ebeam

gdf:
	$(MAKE) -C gdf

gdsii:
	$(MAKE) -C gdsii

lef:
	$(MAKE) -C lef

lp:
	$(MAKE) -C lp

tf:
	$(MAKE) -C tf

verilog:
	$(MAKE) -C verilog

.PHONY: clean
clean:
	$(MAKE) clean -C def
	$(MAKE) clean -C lef

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C def
	$(MAKE) extraclean -C lef
