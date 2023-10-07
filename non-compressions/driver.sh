#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=0-00:15
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=2


order=$1

[ $order -eq $order 2>/dev/null ] || exit 1

sed -i "1s/.*/#define ORDER $order/" ../golay.h

make all

echo Generating Classes

start=`date +%s`
./generate_classes 0 & ./generate_classes 1
wait
end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds

echo Matching Candidates

start=`date +%s`

sort results/$order-unique-filtered-0-0 > results/$order-unique-filtered-0-0.sorted
sort results/$order-unique-filtered-1-0 > results/$order-unique-filtered-1-0.sorted

./match_pairs
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds

candidatesA=$(wc -l < results/$order-unique-filtered-0-0)
candidatesB=$(wc -l < results/$order-unique-filtered-1-0)
pairs=$(wc -l < results/$order-pairs-found)

total=$((runtime1 + runtime2))

python3 -u "print_timings_table.py" $order $candidatesA $candidatesB $pairs $runtime1 $runtime2 $total > results.table