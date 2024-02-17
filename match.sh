#echo Matching Candidates

order=$1
len=$2
proc=$3
i=$4

start=`date +%s`

sort -u -S 1G -T results/$order results/$order/$order-candidates-0_$proc | uniq > results/$order/$order-candidates-a.sorted_$proc
sort -u -S 1G -T results/$order results/$order/$order-candidates-1_$proc | uniq > results/$order/$order-candidates-b.sorted_$proc

#echo Sorting complete
#echo Matching

./bin/match_pairs $order $len $proc $i
end=`date +%s`

runtime2=$((end-start))
#echo $runtime2 seconds