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

sed -n '655074p' results/$order-pairs-found > results/$order-pairs-found-1

./bin/uncompression 1 1 $order $compress $newcompress

#wait

./match.sh 90 45 1

#comm -1 -2 results/90/90-candidates-a.sorted_1 results/90/90-candidates-b.sorted_1 > results/90/1-sols

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

