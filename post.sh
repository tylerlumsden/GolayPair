order=$1

cat ./results/$order/$order-pairs-found-* | uniq > results/$order/$order-pairs-found
rm ./results/$order/$order-pairs-found-*

rm ./results/$order/$order-candidates-0_*
rm ./results/$order/$order-candidates-1_*
rm ./results/$order/$order-candidates-a.sorted_*
rm ./results/$order/$order-candidates-b.sorted_*
rm ./results/$order-pairs-found-*
rm ./results/$order/$order-pairs-found_*