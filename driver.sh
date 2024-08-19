#TO USE: ./driver.sh [ORDER] [Compression Factor]

paf_bound=0

order=$1
compress=$2

len=$(($order / $compress))

[ $order -eq $order 2>/dev/null ] || exit 1
[ $numproc -eq $numproc 2>/dev/null ] || exit 1

mkdir results
mkdir results/history
mkdir results/$order

echo Generating Candidates...

totalstart=`date +%s`

start=`date +%s`
./bin/generate_hybrid $order $compress $paf_bound
end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds elapsed

echo Matching Candidates...

start=`date +%s`

sort results/$order/$order-unique-filtered-a_1 | uniq > results/$order/$order-candidates-a.sorted_1
sort results/$order/$order-unique-filtered-b_1 | uniq > results/$order/$order-candidates-b.sorted_1

./bin/match_pairs $order $len 1
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds elapsed

mv results/$order/$order-pairs-found_1 results/$order/$order-pairs-found-1

total=$((runtime1 + runtime2))

echo $total seconds total

epochtime=$(date +%N)
datetime=$(date +"%Y-%m-%d")

cp results/$order/$order-pairs-found-1 results/history/$order-$compress-$datetime-$epochtime
cp results/$order/$order-pairs-found-1 results/$order-pairs-found

if [ $compress -gt 1 ]
then

echo Uncompressing Pairs...

./uncompress.sh $order $compress 1 0

cp results/$order/$order-pairs-found-0 results/history/$order-1-$datetime-$epochtime
cp results/$order/$order-pairs-found-0 results/$order-pairs-found
fi

totalend=`date +%s`

totaltime=$((totalend-totalstart))

echo $totaltime total seconds elapsed

echo Filtering Equivalences...

start=`date +%s`
./bin/cache_filter $order $order
end=`date +%s`

runtime3=$((end-start))

echo $runtime3 seconds elapsed

epochtime=$(date +%N)
datetime=$(date +"%Y-%m-%d")


cp results/$order-unique-pairs-found results/history/$order-1-$datetime-$epochtime