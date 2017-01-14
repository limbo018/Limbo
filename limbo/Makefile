all: geometry parsers programoptions thirdparty
.PHONY: geometry parsers programoptions thirdparty

geometry:
	$(MAKE) -C geometry

parsers:
	$(MAKE) -C parsers

programoptions:
	$(MAKE) -C programoptions

thirdparty:
	$(MAKE) -C thirdparty
	
.PHONY: clean
clean:
	$(MAKE) clean -C geometry
	$(MAKE) clean -C parsers
	$(MAKE) clean -C programoptions
	$(MAKE) clean -C thirdparty

.PHONY: extraclean
extraclean:
	$(MAKE) extraclean -C geometry
	$(MAKE) extraclean -C parsers
	$(MAKE) extraclean -C programoptions
	$(MAKE) extraclean -C thirdparty
