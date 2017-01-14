# top makefile 

MAKE = make
TEST_DIR = test

# list of components 
PARSERS = limbo/parsers
SOLVERS = limbo/solvers
PROGRAMOPTIONS = limbo/programoptions
THIRDPARTY = limbo/thirdparty

RESRCS = \
		 $(PARSERS)/def/bison \
		 $(PARSERS)/lef/bison \
		 $(PARSERS)/ebeam/bison \
		 $(PARSERS)/lp/bison \
		 $(PARSERS)/verilog/bison \
		 $(PARSERS)/gdf/bison \
		 $(PARSERS)/gdsii/stream \
		 $(PARSERS)/bookshelf/bison \
		 $(SOLVERS)/lpmcf \
		 $(PROGRAMOPTIONS)

.PHONY: build 

build: 
	mkdir -p lib 
	mkdir -p bin
	$(MAKE) -C $(PARSERS)/def/bison
	$(MAKE) all -C $(PARSERS)/lef/bison
	$(MAKE) -C $(PARSERS)/ebeam/bison
	$(MAKE) -C $(PARSERS)/lp/bison
	$(MAKE) -C $(PARSERS)/verilog/bison
	$(MAKE) -C $(PARSERS)/gdf/bison
	$(MAKE) -C $(PARSERS)/gdsii/stream
	$(MAKE) -C $(PARSERS)/bookshelf/bison
	$(MAKE) -C $(PROGRAMOPTIONS)
	$(MAKE) -C $(THIRDPARTY)
	
install:
	mkdir -p lib 
	mkdir -p bin
	$(MAKE) install -C $(PARSERS)/def/bison
	$(MAKE) install -C $(PARSERS)/lef/bison
	$(MAKE) install -C $(PARSERS)/ebeam/bison
	$(MAKE) install -C $(PARSERS)/lp/bison
	$(MAKE) install -C $(PARSERS)/verilog/bison
	$(MAKE) install -C $(PARSERS)/gdf/bison
	$(MAKE) install -C $(PARSERS)/gdsii/stream
	$(MAKE) install -C $(PARSERS)/bookshelf/bison
	$(MAKE) install -C $(PROGRAMOPTIONS)
	$(MAKE) install -C $(THIRDPARTY)

test: 
	$(MAKE) -C $(TEST_DIR)/algorithms
	$(MAKE) -C $(TEST_DIR)/geometry
	$(MAKE) -C $(TEST_DIR)/parsers/def
	$(MAKE) -C $(TEST_DIR)/parsers/lef
	$(MAKE) -C $(TEST_DIR)/parsers/ebeam
	$(MAKE) -C $(TEST_DIR)/parsers/lp
	$(MAKE) -C $(TEST_DIR)/parsers/tf
	$(MAKE) -C $(TEST_DIR)/parsers/verilog
	$(MAKE) -C $(TEST_DIR)/parsers/gdf
	$(MAKE) -C $(TEST_DIR)/parsers/gdsii
	$(MAKE) -C $(TEST_DIR)/parsers/bookshelf
	$(MAKE) -C $(TEST_DIR)/programoptions
	$(MAKE) -C $(TEST_DIR)/solvers/lpmcf
	$(MAKE) -C $(TEST_DIR)/string

clean:
	$(MAKE) extraclean -C $(PARSERS)/def/bison
	$(MAKE) extraclean -C $(PARSERS)/lef/bison
	$(MAKE) extraclean -C $(PARSERS)/ebeam/bison
	$(MAKE) extraclean -C $(PARSERS)/lp/bison
	$(MAKE) extraclean -C $(PARSERS)/verilog/bison
	$(MAKE) extraclean -C $(PARSERS)/gdf/bison
	$(MAKE) extraclean -C $(PARSERS)/gdsii/stream
	$(MAKE) extraclean -C $(PARSERS)/bookshelf/bison
	$(MAKE) extraclean -C $(PROGRAMOPTIONS)
	$(MAKE) extraclean -C $(THIRDPARTY)
	$(MAKE) extraclean -C $(TEST_DIR)/algorithms
	$(MAKE) extraclean -C $(TEST_DIR)/geometry
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/def
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/lef
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/ebeam
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/lp
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/tf
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/verilog
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/gdf
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/gdsii
	$(MAKE) extraclean -C $(TEST_DIR)/parsers/bookshelf
	$(MAKE) extraclean -C $(TEST_DIR)/programoptions
	$(MAKE) extraclean -C $(TEST_DIR)/solvers/lpmcf
	$(MAKE) extraclean -C $(TEST_DIR)/string
