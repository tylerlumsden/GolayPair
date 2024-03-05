#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=1-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%j.out # STDOUT

order=90
compress=6
newcompress=2

############################################### INPUT ABOVE
#make

#mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

sed -n '670898p' results/$order-pairs-found > results/$order-pairs-found-2

#./bin/uncompression 1 2 $order $compress $newcompress

#wait

#order=90
#proc=2

#echo Sorting A

#sort -S 1G -T results/tmp results/$order/$order-candidates-0_$proc | uniq > results/$order/$order-candidates-a.sorted_$proc

#echo Sorting B

./bin/match_pairs 90 45 2

#sort -S 1G -T results/tmp results/$order/$order-candidates-1_$proc | uniq > results/$order/$order-candidates-b.sorted_$proc

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

