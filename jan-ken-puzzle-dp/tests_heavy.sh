#!/bin/bash
shopt -s nullglob

for ext in .in; do
    files=(test/heavy/*"$ext")
    for i in `seq -f %02g ${#files[@]}`; do
        printf "\nRunning test $i\n";
        time (python3 puzzle_hash.py < test/heavy/$i.in | tee test/heavy/results$i);
        diff -y --color test/heavy/results$i test/heavy/$i.out;
    done
done
