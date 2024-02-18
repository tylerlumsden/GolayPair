#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=7-00:00
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%a.out # STDOUT

order=90
compress=6
newcompress=2

############################################### INPUT ABOVE
make

mkdir ./results/$order

linecount=$(wc -l < results/$order-pairs-found)

sed -n '655072p' results/$order-pairs-found > results/$order-pairs-found-1

./bin/uncompression 1 $order $compress $newcompress

wait

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

