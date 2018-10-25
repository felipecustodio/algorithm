#!/bin/bash
shopt -s nullglob

for ext in .in; do
    files=(test/light/*"$ext")
    for i in `seq -f %02g ${#files[@]}`; do
        printf "\nRunning test $i\n";
        time (python puzzle_hash.py < test/light/$i.in | tee test/light/results$i);
        diff -y --color test/light/results$i test/light/$i.out;
    done
done
