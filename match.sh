echo Matching Candidates

order=$1

start=`date +%s`

rm results/$order-candidates-a
rm results/$order-candidates-b


    cat results/$order-unique-filtered-0 >> results/$order-candidates-a
    cat results/$order-unique-filtered-1 >> results/$order-candidates-b


sort results/$order-candidates-a | uniq > results/$order-candidates-a.sorted
sort results/$order-candidates-b | uniq > results/$order-candidates-b.sorted

./bin/match_pairs
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds