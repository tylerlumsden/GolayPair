#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=0-00:15
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=2

#TO USE: ./driver.sh [ORDER] [Compression Factor] [Number of parallel divisions]

order=$1
compress=$2
numproc=$3

len=$(($order / $compress))

[ $order -eq $order 2>/dev/null ] || exit 1
[ $numproc -eq $numproc 2>/dev/null ] || exit 1

make

echo Number of processes: $numproc

start=`date +%s`

for ((i = 0; i<$numproc; i++))
do  
    echo i: $i
    ./bin/generate_orderly $order $compress
done

wait

end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds

echo Matching Candidates

start=`date +%s`

rm results/$order-candidates-a
rm results/$order-candidates-b

for ((i = 0; i<$numproc; i++))
do

    cat results/$order-unique-filtered-0 >> results/$order-candidates-a
    cat results/$order-unique-filtered-1 >> results/$order-candidates-b
done

sort results/$order-candidates-a | uniq > results/$order-candidates-a.sorted
sort results/$order-candidates-b | uniq > results/$order-candidates-b.sorted

./bin/match_pairs $order $len
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds

candidatesA=$(wc -l < results/$order-candidates-a.sorted)
candidatesB=$(wc -l < results/$order-candidates-b.sorted)
pairs=$(wc -l < results/$order-pairs-found)

total=$((runtime1 + runtime2))


#start=`date +%s`
#./bin/filter_equivalent
#end=`date +%s`

#runtime3=$((end-start))

#echo $runtime3 seconds

runtime3=0
uncompressedpairs=0

./bin/filter_equivalent $order $(($order / $compress))

#python3 -u "src/print_timings_table.py" $order $compress $candidatesA $candidatesB $pairs $runtime1 $uncompressedpairs $runtime3 $total > results.table

#start=`date +%s`


#./bin/filter_equivalent

#end=`date +%s`

#runtime3=$((end-start))
#echo $runtime3 seconds