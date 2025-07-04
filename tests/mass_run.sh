#!/bin/bash
set -e

PWD=$(pwd)
echo "Running from $PWD"

RUNS=30
SUCCESS=0
FAIL=0

for i in $(seq 1 $RUNS); do
    echo "Run #$i"
    /root/projects/PokerParlor/build/poker_bot >  $PWD/output_$i.txt 2>&1 || {
        echo "Run $i failed! See tests/output_$i.txt"
        FAIL=$((FAIL + 1))
        continue
    }
    SUCCESS=$((SUCCESS + 1))
done

echo "Completed $RUNS runs: $SUCCESS succeeded, $FAIL failed."