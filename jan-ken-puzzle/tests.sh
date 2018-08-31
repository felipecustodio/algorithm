#!/bin/bash
shopt -s nullglob

for ext in .in; do
    files=(tests/*"$ext")
    printf 'number of testfiles: %d\n' "${#files[@]}"

    for i in `seq 1 ${#files[@]}`; do
        rm results$i.out;
        printf "\nRunning test $i\n";
        ./puzzle < tests/$i.in 2>&1 | tee tests/results$i.out;
        # vimdiff tests/results$i.out tests/$i.out;
        diff tests/results$i.out tests/$i.out;
        printf ".....................\n";
    done
done