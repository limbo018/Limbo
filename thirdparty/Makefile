#==========================================================================
#                   Top Makefile for Third Party Packages
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ..)

CSDP_SRCS = Csdp
OPENBLAS_SRCS = OpenBLAS
CSDP_LIB = $(LIMBO_ROOT_DIR)/lib/libsdp.a
OPENBLAS_LIB = $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a

all: $(CSDP_LIB) $(OPENBLAS_LIB)
	@echo ">> building default"

$(OPENBLAS_LIB): 
	@echo ">> building OpenBLAS"
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh make; cd .."
	mv $(OPENBLAS_SRCS)/libopenblas_nehalem-r0.2.14.a $(OPENBLAS_LIB)

$(CSDP_LIB): $(OPENBLAS_LIB)
	@echo ">> building Csdp"
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh make; cd .."
	mv $(CSDP_SRCS)/lib/libsdp.a $(CSDP_LIB)

install: $(OPENBLAS_LIB) $(CSDP_LIB) clean
	@echo ">> building install"

.PHONY: clean
clean: 
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh clean; cd .."
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh clean; cd .."

.PHONY: extraclean
extraclean: 
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh extraclean; cd .."
	rm -f $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh extraclean; cd .."
	rm -f $(LIMBO_ROOT_DIR)/lib/libsdp.a
