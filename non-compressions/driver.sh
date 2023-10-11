#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=0-00:15
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=2

#TO USE: ./driver.sh [ORDER] [Number of parallel divisions]

order=$1
numproc=$2

[ $order -eq $order 2>/dev/null ] || exit 1
[ $numproc -eq $numproc 2>/dev/null ] || exit 1


sed -i "1s/.*/#define ORDER $order/" ../golay.h

make all

echo Number of processes: $numproc

start=`date +%s`

for ((i = 1; i<=$numproc; i++))
do  
    echo i: $i
    ./generate_orderly 0 $i $numproc & ./generate_orderly 1 $i $numproc &
done

wait
end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds

echo Matching Candidates

start=`date +%s`


for ((i = 1; i<=$numproc; i++))
do
    cat results/$order-unique-filtered-0-$i >> results/$order-candidates-a
    cat results/$order-unique-filtered-1-$i >> results/$order-candidates-b
done

sort results/$order-candidates-a | uniq > results/$order-candidates-a.sorted
sort results/$order-candidates-b | uniq > results/$order-candidates-b.sorted

./match_pairs
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds

candidatesA=$(wc -l < results/$order-candidates-a.sorted)
candidatesB=$(wc -l < results/$order-candidates-b.sorted)
pairs=$(wc -l < results/$order-pairs-found)

total=$((runtime1 + runtime2))

python3 -u "print_timings_table.py" $order $candidatesA $candidatesB $pairs $runtime1 $runtime2 $total > results.table


start=`date +%s`
./filter_equivalent
end=`date +%s`

runtime3=$((end-start))

echo $runtime3 seconds