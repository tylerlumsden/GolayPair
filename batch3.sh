#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=3-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%a.out # STDOUT

#order=90
#compress=6
#newcompress=2

############################################### INPUT ABOVE
#make

#mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

#sed -n '670903p' results/$order-pairs-found > results/$order-pairs-found-3

#./bin/uncompression 1 3 $order $compress $newcompress

#wait

./match.sh 90 45 3

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

