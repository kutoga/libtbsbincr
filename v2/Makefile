CPPFLAGS=-Wall -Wextra -Werror -O3 -fPIC
CFLAGS=-std=c11

# Enable logging
CFLAGS += -DTBS_LOG_ENABLE

LDFLAGS:=-lm

CFILES=$(shell find src -name '*.c')
OFILES=$(CFILES:.c=.o)

DEP=.dep

TARGETS=libtbsenc.a

.PHONY: all clean
.SECONDARY:

all: $(TARGETS)

# Load dependencies.
# The dependency logic is based on the following two links:
# http://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
# http://stackoverflow.com/questions/313778/generate-dependencies-for-a-makefile-for-a-project-in-c-c
DEP_FILES:=$(shell [ -d '$(DEP)' ] && find $(DEP) -name '*.d')
-include $(DEP_FILES)

clean:
	$(RM) -r $(find src -name '*.o') $(TARGETS) $(OFILES) $(DEP)

%.o: %.c
	@mkdir -p $(DEP)/$(dir $<)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MM -MT '$@' $< > $(DEP)/$<.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.a: $(OFILES)
	@mkdir -p $(@D)
	$(AR) crfsT $@ $^

test: test.c libtbsenc.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

