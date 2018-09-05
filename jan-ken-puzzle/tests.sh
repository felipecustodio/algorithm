#!/bin/bash
shopt -s nullglob

for ext in .in; do
    files=(test/*"$ext")
    printf 'number of testfiles: %d\n' "${#files[@]}"

    for i in `seq 1 ${#files[@]}`; do
        rm results$i.out;
        printf "\nRunning test $i\n";
        ./puzzle < test/$i.in 2>&1 | tee test/results$i.out;
        # vimdiff tests/results$i.out tests/$i.out;
        diff test/results$i.out test/$i.out;
        printf ".....................\n";
    done
done
