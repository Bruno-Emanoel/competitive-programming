#!/bin/bash
# Run this file as profile.sh <code1.cpp> <code2.cpp> > results.txt

N=10 # Number of tests to run, you can change this value as needed

file_name1="$1" # First command line argument, expected to be the first C++ file
file_name2="$2" # Second command line argument, expected to be the second C++ file

if [ -z "$file_name1" ] || [ -z "$file_name2" ]; then
    echo "Usage: $0 <code1.cpp> <code2.cpp>"
    exit 1
fi

g++ -std=c++20 -Ofast gen.cpp -o gen.exe # It's expected to have a gen.cpp as case generator to avoid biased results
g++ -std=c++20 -O2 "$file_name1" -o code1.exe
g++ -std=c++20 -O2 "$file_name2" -o code2.exe

echo "Arquivos compilados"


TIMEFORMAT=%R

i=1
while [ $i -le $N ] ; do
    echo "--------- Teste $i ---------"
    ./gen $i > in
    echo "Tempo para code1: "
    var=$( { time ./code1 < in > out; } 2>&1 )
    echo "$var"
    echo "Tempo para code2: "
    var=$( { time ./code2 < in > ok; } 2>&1 )
    echo "$var"
    ((++i))
done

rm ./gen.exe
rm ./code1.exe
rm ./code2.exe
rm in
rm out
rm ok