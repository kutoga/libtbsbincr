#!/bin/bash
GCC=$(./gcc_resolv.sh $1)
$GCC -v 2>&1| grep Target | awk '{print$2}'

