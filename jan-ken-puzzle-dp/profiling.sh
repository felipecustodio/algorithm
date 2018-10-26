time (python -m cProfile -s cumtime -o puzzle_hash.cprof puzzle_hash.py < test/heavy/05.in)
pyprof2calltree -k -i puzzle_hash.cprof
