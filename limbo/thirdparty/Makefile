#==========================================================================
#                   Top Makefile for Third Party Packages
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)

CSDP_SRCS = Csdp
OPENBLAS_SRCS = OpenBLAS
LIBLINEAR_SRCS = liblinear
CTHREADPOOL_SRCS = CThreadPool
DLX_SRCS = dlx

CSDP_LIB = $(LIMBO_ROOT_DIR)/lib/libsdp.a
OPENBLAS_LIB = $(LIMBO_ROOT_DIR)/lib/libopenblas-st.a
LIBLINEAR_LIB = $(LIMBO_ROOT_DIR)/lib/liblinear.a
CTHREADPOOL_LIB = $(LIMBO_ROOT_DIR)/lib/libthpool.a
DLX_LIB = $(LIMBO_ROOT_DIR)/lib/libdlx.a

#==========================================================================
#                         Compilation Flags
# ==========================================================================

# default OPENBLAS is off 
OPENBLAS = 0
# default DBG is off
DBG = 0

# include environmental configurations 
include $(LIMBO_ROOT_DIR)/Include.mk

ifeq ($(DBG), 1)
	CXXFLAGS = $(CXXFLAGS_DEBUG)
else
	CXXFLAGS = $(CXXFLAGS_RELEASE)
endif

# ==========================================================================
#                         Standard Setting
# ==========================================================================

ifeq ($(OPENBLAS), 1)
all: $(CSDP_LIB) $(OPENBLAS_LIB) $(LIBLINEAR_LIB) $(CTHREADPOOL_LIB) $(DLX_LIB)
	@echo ">> building default with OPENBLAS on"
else 
all: $(CTHREADPOOL_LIB) $(DLX_LIB)
	@echo ">> building default with OPENBLAS off"
endif 

.PHONY: $(OPENBLAS_LIB) $(CSDP_LIB) $(LIBLINEAR_LIB) $(CTHREADPOOL_LIB) $(DLX_LIB)

$(OPENBLAS_LIB): 
	@echo ">> building OpenBLAS"
	$(MAKE) -C $(OPENBLAS_SRCS) -f Makefile.limbo
	mv $(OPENBLAS_SRCS)/OpenBLAS/libopenblas_*.a $(OPENBLAS_LIB) # the name may vary from architectures 

$(CSDP_LIB): $(OPENBLAS_LIB)
	@echo ">> building Csdp"
	$(MAKE) -C $(CSDP_SRCS)
	mv $(CSDP_SRCS)/lib/libsdp.a $(CSDP_LIB)
	mv $(CSDP_SRCS)/solver/csdp $(LIMBO_ROOT_DIR)/bin

$(LIBLINEAR_LIB): $(OPENBLAS_LIB)
	@echo ">> building liblinear"
	$(MAKE) -C $(LIBLINEAR_SRCS)
	mv $(LIBLINEAR_SRCS)/liblinear.a $(LIBLINEAR_LIB)
	mv $(LIBLINEAR_SRCS)/train $(LIMBO_ROOT_DIR)/bin/liblinear-train
	mv $(LIBLINEAR_SRCS)/predict $(LIMBO_ROOT_DIR)/bin/liblinear-predict 

$(CTHREADPOOL_LIB):
	@echo ">> build CThreadPool"
	$(MAKE) -C $(CTHREADPOOL_SRCS) 

$(DLX_LIB):
	@echo ">> build dlx"
	$(MAKE) -C $(DLX_SRCS)

install: $(OPENBLAS_LIB) $(CSDP_LIB) $(LIBLINEAR_LIB) $(CTHREADPOOL_LIB) $(DLX_LIB) clean
	@echo ">> building install"

.PHONY: clean
clean: 
	$(MAKE) -C $(OPENBLAS_SRCS) clean -f Makefile.limbo
	$(MAKE) -C $(CSDP_SRCS) clean
	$(MAKE) -C $(LIBLINEAR_SRCS) clean
	$(MAKE) -C $(CTHREADPOOL_SRCS) clean
	$(MAKE) -C $(DLX_SRCS) clean

.PHONY: extraclean
extraclean: clean
	rm -f $(OPENBLAS_LIB)
	rm -f $(CSDP_LIB)
	rm -f $(LIMBO_ROOT_DIR)/bin/csdp
	rm -f $(LIBLINEAR_LIB)
	rm -f $(LIMBO_ROOT_DIR)/bin/liblinear-train
	rm -f $(LIMBO_ROOT_DIR)/bin/liblinear-predict
	rm -f $(CTHREADPOOL_LIB)
	rm -f $(DLX_LIB)
