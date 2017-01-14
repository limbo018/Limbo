all: bookshelf def ebeam gdf gdsii lef lp tf verilog
.PHONY: bookshelf def ebeam gdf gdsii lef lp tf verilog

bookshelf:
	$(MAKE) -C bookshelf/bison

def:
	$(MAKE) -C def/bison

ebeam:
	$(MAKE) -C ebeam/bison

gdf:
	$(MAKE) -C gdf/bison

gdsii:
	$(MAKE) -C gdsii/stream

lef:
	$(MAKE) -C lef/bison

lp:
	$(MAKE) -C lp/bison

tf:

verilog:
	$(MAKE) -C verilog/bison

.PHONY: clean
clean:
	$(MAKE) clean -C bookshelf/bison
	$(MAKE) clean -C def/bison
	$(MAKE) clean -C ebeam/bison
	$(MAKE) clean -C gdf/bison
	$(MAKE) clean -C gdsii/stream
	$(MAKE) clean -C lef/bison
	$(MAKE) clean -C lp/bison
	$(MAKE) clean -C verilog/bison

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C bookshelf/bison
	$(MAKE) extraclean -C def/bison
	$(MAKE) extraclean -C ebeam/bison
	$(MAKE) extraclean -C gdf/bison
	$(MAKE) extraclean -C gdsii/stream
	$(MAKE) extraclean -C lef/bison
	$(MAKE) extraclean -C lp/bison
	$(MAKE) extraclean -C verilog/bison
