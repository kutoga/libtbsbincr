#!/bin/bash
GCC=$(./gcc_resolv.sh $1)
VERSION=$(./gcc_version.sh $GCC)
TARGET=$(./gcc_target.sh $GCC)

CACHE=".cache_${GCC}_${TARGET}_${VERSION}"
if [ -f "$CACHE" ]; then
    cat $CACHE
    exit
fi

# Assume g++ flags are equal to the gcc ones
if [ "$GCC" == "g++" ]; then
    GCC=gcc
fi 

URL=https://gcc.gnu.org/onlinedocs/gcc-$VERSION/gcc/Optimize-Options.html#Optimize-Options
FLAGS=$(curl --silent $URL 2>&1 | egrep -o '\-f[0-9a-zA-Z-]+' | grep -hv '^-fno-' | sort | uniq)

echo $FLAGS > $CACHE

# Print flags
echo $FLAGS

