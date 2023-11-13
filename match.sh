echo Matching Candidates

order=$1
numproc=$2

start=`date +%s`

rm results/$order-candidates-a
rm results/$order-candidates-b

for ((i = 0; i<$numproc; i++))
do

    cat results/$order-unique-filtered-0-$i-1 >> results/$order-candidates-a
    cat results/$order-unique-filtered-1-$i-1 >> results/$order-candidates-b
done

sort results/$order-candidates-a | uniq > results/$order-candidates-a.sorted
sort results/$order-candidates-b | uniq > results/$order-candidates-b.sorted

./bin/match_pairs
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds

candidatesA=$(wc -l < results/$order-candidates-a.sorted)
candidatesB=$(wc -l < results/$order-candidates-b.sorted)
pairs=$(wc -l < results/$order-pairs-found)

total=$((runtime1 + runtime2))

python3 -u "src/print_timings_table.py" $order $candidatesA $candidatesB $pairs $runtime1 $runtime2 $total > results.table


start=`date +%s`
./bin/filter_equivalent
end=`date +%s`

runtime3=$((end-start))

echo $runtime3 seconds