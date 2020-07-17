CPPFLAGS=-Wall -Wextra -Werror -O3 -fPIC -I include
CFLAGS=-std=gnu11
CXXFLAGS=-std=gnu++17

# Enable logging
CPPFLAGS += -DTBS_LOG_ENABLE

LDFLAGS:=-lm

CFILES=$(shell find src -name '*.c')
OFILES=$(CFILES:.c=.o)

TEST_CPPFILES=$(shell find tests -name '*.cc')
TEST_CFILES=$(shell find tests -name '*.c')
TEST_OFILES=$(TEST_CPPFILES:.cc=.o) $(TEST_CFILES:.c=.o)

EXAMPLES_CFILES=$(shell find examples -name '*.c')
EXAMPLES=$(EXAMPLES_CFILES:.c=)

DEP=.dep

TARGETS=libtbsenc.a test

.PHONY: all clean check examples
.SECONDARY:

all: $(TARGETS)

# Load dependencies.
# The dependency logic is based on the following two links:
# http://stackoverflow.com/questions/8025766/makefile-auto-dependency-generation
# http://stackoverflow.com/questions/313778/generate-dependencies-for-a-makefile-for-a-project-in-c-c
DEP_FILES:=$(shell [ -d '$(DEP)' ] && find $(DEP) -name '*.d')
-include $(DEP_FILES)

clean:
	$(RM) -r $(find src -name '*.o') $(TARGETS) $(OFILES) $(TEST_OFILES) $(DEP) tests/main $(EXAMPLES)

examples: $(EXAMPLES)

%.o: %.c
	@mkdir -p $(DEP)/$(dir $<)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -MM -MT '$@' $< > $(DEP)/$<.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cc
	@mkdir -p $(DEP)/$(dir $<)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM -MT '$@' $< > $(DEP)/$<.d
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.a: $(OFILES)
	@mkdir -p $(@D)
	$(AR) crfsT $@ $^

test: test.o libtbsenc.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

tests/main: $(TEST_OFILES) libtbsenc.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -lgtest -lpthread -o $@

examples/%: examples/%.o libtbsenc.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -lpthread -o $@

check: tests/main
	./$<

