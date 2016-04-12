#==========================================================================
#                   Top Makefile for Third Party Packages
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)

CSDP_SRCS = Csdp
OPENBLAS_SRCS = OpenBLAS
LIBLINEAR_SRCS = liblinear
CTHREADPOOL_SRCS = CThreadPool
CSDP_LIB = $(LIMBO_ROOT_DIR)/lib/libsdp.a
OPENBLAS_LIB = $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a
LIBLINEAR_LIB = $(LIMBO_ROOT_DIR)/lib/liblinear.a
CTHREADPOOL_LIB = $(LIMBO_ROOT_DIR)/lib/libthpool.a

all: $(CSDP_LIB) $(OPENBLAS_LIB) $(LIBLINEAR_LIB)
	@echo ">> building default"

$(OPENBLAS_LIB): 
	@echo ">> building OpenBLAS"
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh make; cd .."
	mv $(OPENBLAS_SRCS)/libopenblas_*-r0.2.14.a $(OPENBLAS_LIB) # the name may vary from architectures 

$(CSDP_LIB): $(OPENBLAS_LIB)
	@echo ">> building Csdp"
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh make; cd .."
	mv $(CSDP_SRCS)/lib/libsdp.a $(CSDP_LIB)
	mv $(CSDP_SRCS)/solver/csdp $(LIMBO_ROOT_DIR)/bin

$(LIBLINEAR_LIB): $(OPENBLAS_LIB)
	@echo ">> building liblinear"
	@bash -c "cd $(LIBLINEAR_SRCS); make; cd .."
	mv $(LIBLINEAR_SRCS)/liblinear.a $(LIBLINEAR_LIB)
	mv $(LIBLINEAR_SRCS)/train $(LIMBO_ROOT_DIR)/bin/liblinear-train
	mv $(LIBLINEAR_SRCS)/predict $(LIMBO_ROOT_DIR)/bin/liblinear-predict 

$(CTHREADPOOL_LIB):
	@echo ">> build CThreadPool"
	@bash -c "cd $(CTHREADPOOL_SRCS); make; cd .."

install: $(OPENBLAS_LIB) $(CSDP_LIB) $(LIBLINEAR_LIB) $(CTHREADPOOL_LIB) clean
	@echo ">> building install"

.PHONY: clean
clean: 
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh clean; cd .."
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh clean; cd .."
	@bash -c "cd $(LIBLINEAR_SRCS); make clean; cd .."
	@bash -c "cd $(CTHREADPOOL_SRCS); make clean; cd .."

.PHONY: extraclean
extraclean: 
	@bash -c "cd $(OPENBLAS_SRCS); source easy_make.sh extraclean; cd .."
	rm -f $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a
	@bash -c "cd $(CSDP_SRCS); source easy_make.sh extraclean; cd .."
	rm -f $(LIMBO_ROOT_DIR)/lib/libsdp.a
	rm -f $(LIMBO_ROOT_DIR)/bin/csdp
	@bash -c "cd $(LIBLINEAR_SRCS); make clean; cd .."
	rm -f $(LIMBO_ROOT_DIR)/lib/liblinear.a
	rm -f $(LIMBO_ROOT_DIR)/bin/liblinear-train
	rm -f $(LIMBO_ROOT_DIR)/bin/liblinear-predict
	@bash -c "cd $(CTHREADPOOL_SRCS); make extraclean; cd .."
