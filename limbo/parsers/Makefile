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
	$(MAKE) -C gdsii/gdsdb

lef:
	$(MAKE) -C lef/bison

lp:
	$(MAKE) -C lp/bison

tf:

verilog:
	$(MAKE) -C verilog/bison

.PHONY: install
install:
	$(MAKE) install -C bookshelf/bison
	$(MAKE) install -C def/bison
	$(MAKE) install -C def/spirit
	$(MAKE) install -C ebeam/bison
	$(MAKE) install -C ebeam/spirit
	$(MAKE) install -C gdf/bison
	$(MAKE) install -C gdsii/stream
	$(MAKE) install -C gdsii/gdsdb
	$(MAKE) install -C gdsii/ascii/spirit
	$(MAKE) install -C lef/bison
	$(MAKE) install -C lef/spirit
	$(MAKE) install -C lp/bison
	$(MAKE) install -C tf/spirit
	$(MAKE) install -C verilog/bison

.PHONY: clean
clean:
	$(MAKE) clean -C bookshelf/bison
	$(MAKE) clean -C def/bison
	$(MAKE) clean -C ebeam/bison
	$(MAKE) clean -C gdf/bison
	$(MAKE) clean -C gdsii/stream
	$(MAKE) clean -C gdsii/gdsdb
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
	$(MAKE) extraclean -C gdsii/gdsdb
	$(MAKE) extraclean -C lef/bison
	$(MAKE) extraclean -C lp/bison
	$(MAKE) extraclean -C verilog/bison
