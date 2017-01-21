#==========================================================================
#                   Top Makefile for Third Party Packages
# ==========================================================================

LIMBO_ROOT_DIR = $(realpath ../..)
LIBDIR = $(LIMBO_ROOT_DIR)/lib

CSDP_SRCS = Csdp
OPENBLAS_SRCS = OpenBLAS
LIBLINEAR_SRCS = liblinear
CTHREADPOOL_SRCS = CThreadPool
DLX_SRCS = dlx
LIBDIVIDE_SRCS = libdivide
FLEX_SRCS = flex

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

$(CSDP_LIB): $(OPENBLAS_LIB)
	@echo ">> building Csdp"
	$(MAKE) -C $(CSDP_SRCS)

$(LIBLINEAR_LIB): $(OPENBLAS_LIB)
	@echo ">> building liblinear"
	$(MAKE) -C $(LIBLINEAR_SRCS)
	mv $(LIBLINEAR_SRCS)/liblinear.a $(LIBLINEAR_LIB)
	@mkdir -p $(LIMBO_ROOT_DIR)/bin
	mv $(LIBLINEAR_SRCS)/train $(LIMBO_ROOT_DIR)/bin/liblinear-train
	mv $(LIBLINEAR_SRCS)/predict $(LIMBO_ROOT_DIR)/bin/liblinear-predict 

$(CTHREADPOOL_LIB):
	@echo ">> build CThreadPool"
	$(MAKE) -C $(CTHREADPOOL_SRCS) 

$(DLX_LIB):
	@echo ">> build dlx"
	$(MAKE) -C $(DLX_SRCS)

install: 
	@echo ">> building install"
ifneq ($(wildcard $(CSDP_LIB)),)
	$(MAKE) install -C $(CSDP_SRCS)
endif
ifneq ($(wildcard $(OPENBLAS_LIB)),)
	$(MAKE) install -C $(OPENBLAS_SRCS) -f Makefile.limbo
endif 
ifneq ($(wildcard $(LIBLINEAR_LIB)),)
	$(MAKE) install -C $(LIBLINEAR_SRCS)
endif 
	$(MAKE) install -C $(CTHREADPOOL_SRCS)
	$(MAKE) install -C $(DLX_SRCS)
	$(MAKE) install -C $(LIBDIVIDE_SRCS)
	$(MAKE) install -C $(FLEX_SRCS)

.PHONY: clean
clean: 
	$(MAKE) clean -C $(OPENBLAS_SRCS) -f Makefile.limbo
	$(MAKE) clean -C $(CSDP_SRCS) 
	$(MAKE) clean -C $(LIBLINEAR_SRCS)
	$(MAKE) clean -C $(CTHREADPOOL_SRCS)
	$(MAKE) clean -C $(DLX_SRCS)
	$(MAKE) clean -C $(LIBDIVIDE_SRCS)
	$(MAKE) clean -C $(FLEX_SRCS)

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
