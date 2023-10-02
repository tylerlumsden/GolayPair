#!/bin/bash

order=$1

[ $order -eq $order 2>/dev/null ] || exit 1

sed -i "1s/.*/#define ORDER $order/" ../golay.h

make all

echo Generating Classes

start=`date +%s`
./generate_classesA & ./generate_classesB
wait
end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds

echo Matching Candidates

start=`date +%s`

sort results/$order-unique-filtered-a-0 > results/$order-unique-filtered-a-0.sorted
sort results/$order-unique-filtered-b-0 > results/$order-unique-filtered-b-0.sorted

./match_pairs
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds

candidatesA=$(wc -l < results/$order-unique-filtered-a-0)
candidatesB=$(wc -l < results/$order-unique-filtered-b-0)
pairs=$(wc -l < results/$order-pairs-found)

total=$((runtime1 + runtime2))

python3 -u "print_timings_table.py" $order $candidatesA $candidatesB $pairs $runtime1 $runtime2 $total > results.table