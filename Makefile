# Compiler / strip
CC:=gcc

CFLAGS:=-O0
override CFLAGS+=-g -Wall -Wextra
# -fPIC
#CFLAGS+=-fno-unswitch-loops

override CFLAGS+=-DTBS_LOG_DISABLE
#CFLAGS+=-DTBS_LOG_DISABLETBS_LOG_MUTEX_T
#CFLAGS+=-DTBS_BINCR_DISABLE

# -O3 -std=c++11 -stdlib=libc++

LDFLAGS:=-lm
#-std=c++11 -stdlib=libc++
STRIP:=strip
AR=ar

# Doxygen
DOXYGEN:=doxygen
DOXYGEN_FLAGS:=
DOXYGEN_CONF:=doxygen.conf

# Dirs / files-extensions
ARCHD:=arch
SRC:=src
INC:=include
BIN:=bin
BIN_EXT:=
SO_EXT:=.so
SL_EXT:=.a
OBJ:=obj
OBJ_EXT:=.o
DEP:=dep
DEP_EXT:=.dep
C_EXT:=.c
TEST=test
PREFIX:=/usr/local

# Kdevelop
KDEV=kdevelop
KDEV_INC=.kdev_include_paths
KDEV_FILES=$(shell find $(SRC) -name '*.cpp' -type f; find $(SRC) $(INC) -name '*.h' -type f)

# Edit the flags
override CFLAGS+=-I$(INC) -I$(SRC)
LDFLAGS+=-L$(BIN)

# Autogenerated flags
FFLAGSD:=flags

# Include arch-files
ifeq ($(ARCH),)
	ARCH:=local
endif
ifeq ($(ARCH),win64)
	CXXFLAGS+=-Dwin64
endif
-include $(ARCHD)/$(ARCH)

# Add now the optional c flags
CC_TARGET:=$(shell cd scripts; ./gcc_target.sh $(CC))
CC_VERSION:=$(shell cd scripts; ./gcc_version.sh $(CC))
CC_FLAGS:=$(CC)_$(CC_TARGET)_$(CC_VERSION)

OPT:=$(shell cat flags/$(CC_FLAGS) 2>/dev/null)
CFLAGS+=$(OPT)

export

# The targets
TARGETS= $(BIN)/tbs/bincr/libtbs-bincr-minimal$(SL_EXT) $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT) $(BIN)/tbs/bincr/example$(BIN_EXT)
TARGETS+=$(BIN)/tbs/bincr/example2$(BIN_EXT) $(BIN)/tbs/bincr/example3$(BIN_EXT) $(BIN)/tbs/bincr/optimization_test$(BIN_EXT)
#$(BIN)/tbs/bincr/encrypt$(BIN_EXT) $(BIN)/tbs/bincr/decrypt$(BIN_EXT)
TARGETS+=$(BIN)/tbs/bincr/crypt$(BIN_EXT)
TARGETS+=$(BIN)/tbs/log/libtbs-log$(SL_EXT) $(BIN)/tbs/log/example$(BIN_EXT)

#TARGETS=$(BIN)/test$(BIN_EXT) $(BIN)/libtest$(SL_EXT) $(BIN)/libtest$(SO_EXT)

.PHONY: all clean mrproper $(FFLAGSD) show_flags install uninstall docs kdev
.SECONDARY:

all: $(TARGETS)

# Load dependencies.
# The dependency logic is based on the following two links:
# http://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
# http://stackoverflow.com/questions/313778/generate-dependencies-for-a-makefile-for-a-project-in-c-c
DEP_FILES:=$(shell [ -d '$(DEP)' ] && find $(DEP) -name '*$(DEP_EXT)')
-include $(DEP_FILES)

clean:
	@echo "CLEAN..."
	@$(RM) -R $(BIN) $(OBJ) $(DEP) $(KDEV_INC) $(TEST) docs

mrproper: clean
	@echo "MRPROPER..."
	@$(RM) -R $(FFLAGSD) scripts/.cache_*

install: all
	@echo "INSTALL..."
	@mkdir -p $(PREFIX)/bin $(PREFIX)/lib
	@cp $(BIN)/test$(BIN_EXT) $(PREFIX)/bin/test$(BIN_EXT)
	@cp $(BIN)/libtest$(SO_EXT) $(PREFIX)/lib/libtest$(SO_EXT)

uninstall:
	@echo "UNINSTALL..."
	@$(RM) $(PREFIX)/bin/test$(BIN_EXT) $(PREFIX)/lib/libtest$(SO_EXT)

docs:
	@echo "DOXYGEN..."
	@$(DOXYGEN) $(DOXYGEN_FLAGS) $(DOXYGEN_CONF)

kdev: $(KDEV_INC)
	@$(KDEV) $(KDEV_FILES)

$(FFLAGSD):
	@mkdir -p $(FFLAGSD)
	(cd scripts; ./gcc_test.sh $(CC) "CC=$(CC) ARCH=$(ARCH) STRIP=$(STRIP) BIN_EXT=$(BIN_EXT)" $(BIN_EXT)) > $@/$(CC_FLAGS)

show_flags:
	@echo $(OPT)

$(KDEV_INC):
	@echo $(shell pwd)/$(SRC) > $@; echo $(shell pwd)/$(INC) >> $@

$(OBJ)/%$(OBJ_EXT): $(SRC)/%$(C_EXT)
	@mkdir -p $(DEP)/$(dir $*)
	@echo "DEP $(DEP)/$*$(DEP_EXT)..."
	@$(CC) $(CFLAGS) -MM -MT '$(patsubst $(SRC)/%$(C_EXT),$(OBJ)/%$(OBJ_EXT),$<)' $< > $(DEP)/$*$(DEP_EXT)
	@mkdir -p $(@D)
	@echo "CC $@..."
	$(CC) $(CFLAGS) -o $@ -c $<

$(BIN)/%$(SO_EXT):
	@mkdir -p $(@D)
	@echo "LD $@..."
	$(CC) -fPIC -shared -o $@ $^ $(LDFLAGS)

$(BIN)/%$(SL_EXT):
	@mkdir -p $(@D)
	@echo "AR $@..."
	$(AR) crfsT $@ $^

$(BIN)/%$(BIN_EXT): $(OBJ)/%$(OBJ_EXT)
	@mkdir -p $(@D)
	@echo "LD $@..."
	$(CC) -o $@ $^ $(LDFLAGS)
	@if [ ! -z '$(STRIP)' ]; then echo "STRIP $@..."; $(STRIP) -s $@; fi

$(TEST)/%$(SO_EXT): $(OBJ)/gtest/gtest-all$(OBJ_EXT)
	@mkdir -p $(@D)
	@echo "LD $@..."
	$(CC) -fPIC -shared -o $@ $^ $(LDFLAGS) -lpthread

$(TEST)/%$(SL_EXT): $(OBJ)/gtest/gtest-all$(OBJ_EXT)
	@mkdir -p $(@D)
	@echo "AR $@..."
	$(AR) crfsT $@ $^

$(TEST)/%$(BIN_EXT): $(OBJ)/gtest/gtest-all$(OBJ_EXT) $(OBJ)/$(TEST)/%$(OBJ_EXT)
	@mkdir -p $(@D)
	@echo "LD $@..."
	$(CC) -o $@  $^ $(LDFLAGS) -lpthread

$(BIN)/tbs/bincr/libtbs-bincr-minimal$(SL_EXT): $(OBJ)/tbs/log/core$(OBJ_EXT) $(OBJ)/tbs/bincr/minimal$(OBJ_EXT)

$(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT): $(OBJ)/tbs/log/core$(OBJ_EXT) $(OBJ)/tbs/bincr/minimal$(OBJ_EXT) $(OBJ)/tbs/bincr/keygen$(OBJ_EXT) $(OBJ)/tbs/bincr/core$(OBJ_EXT)

$(BIN)/tbs/bincr/example$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

$(BIN)/tbs/bincr/example2$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

$(BIN)/tbs/bincr/example3$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

$(BIN)/tbs/bincr/optimization_test$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

#$(BIN)/tbs/bincr/encrypt$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

#$(BIN)/tbs/bincr/decrypt$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

$(BIN)/tbs/bincr/crypt$(BIN_EXT): $(BIN)/tbs/bincr/libtbs-bincr$(SL_EXT)

$(BIN)/tbs/log/libtbs-log$(SL_EXT): $(OBJ)/tbs/log/core$(OBJ_EXT)

$(BIN)/tbs/log/example$(BIN_EXT): $(BIN)/tbs/log/libtbs-log$(SL_EXT)
