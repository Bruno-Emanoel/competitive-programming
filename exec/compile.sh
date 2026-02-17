#!/bin/bash

if [ -z "$1" ]; then
  filename="code.cpp"
else
  filename="$1"
fi

g++ "$filename" -o a.exe -O3 -Wall -Wextra -pedantic -Wfloat-equal -Wshift-overflow=2 -Wduplicated-cond \
 -Wno-variadic-macros -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC  -std=c++20 -DLOCAL
 
if [ $? -ne 0 ]; then
    echo "Compilation Error"
    if [ -f a.exe ]; then
        rm a.exe
    fi
    exit 1
fi
