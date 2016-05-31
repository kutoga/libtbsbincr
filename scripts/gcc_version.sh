#!/bin/bash
GCC=$(./gcc_resolv.sh $1)
$GCC -v 2>&1|grep -o '[0-9]\.[0-9]\.[0-9]'|tail -1

