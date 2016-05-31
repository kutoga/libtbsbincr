#!/bin/bash
GCC=$1
MAKE_FLAGS=$2
BIN_EXT=$3

FFLAGS=$(./gcc_fflags.sh $GCC)

GOOD='test01 ok'
for i in $(seq -w 2 11); do
    GOOD=$GOOD".*?test$i ok";
done

BINARY=bin/tbs/bincr/optimization_test$BIN_EXT
CRYPT=bin/tbs/bincr/crypt$BIN_EXT
CODE="$BINARY; $CRYPT -e $BINARY; cp $BINARY $BINARY.copy; $BINARY; $CRYPT -r $BINARY; diff $BINARY $BINARY.copy || $BINARY; rm $BINARY.copy"

# The binary is executed three times, so the output should be there three times
GOOD="$GOOD.*$GOOD.*$GOOD"


../../param_tester/test_params.pl "(cd ..; make 'OPT=[PARAMS]' $MAKE_FLAGS clean $BINARY $CRYPT; $CODE) 2>&1" "$GOOD" '(gcda not found)|(Segmentation fault)' $FFLAGS 2>/dev/null

# Play with example0, but that code is not too nice
#../../param_tester/test_params.pl '(cd ..; make "OPT=[PARAMS]" clean all; bin/tbs/bincr/encrypt bin/tbs/bincr/example; bin/tbs/bincr/example) 2>&1' 'i is now: 3' 'gcda not found' $FFLAGS 2>/dev/null



