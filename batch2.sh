#!/bin/bash
<<<<<<< HEAD
#SBATCH --account=def-cbright
#SBATCH --time=7-00:00
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%a.out # STDOUT
=======
#SBATCH --account=rrg-cbright
#SBATCH --time=1-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%j.out # STDOUT
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

order=90
compress=6
newcompress=2

############################################### INPUT ABOVE
<<<<<<< HEAD
make

mkdir ./results/$order

linecount=$(wc -l < results/$order-pairs-found)

./split.sh 90 2

./bin/uncompression 670898 2 $order $compress $newcompress

wait
=======
#make

#mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

sed -n '670900p' results/$order-pairs-found > results/$order-pairs-found-2

./bin/uncompression 1 2 $order $compress $newcompress

#wait

#order=90
#proc=2

#echo Sorting A

#sort -S 1G -T results/tmp results/$order/$order-candidates-0_$proc | uniq > results/$order/$order-candidates-a.sorted_$proc

#echo Sorting B

./bin/match_pairs 90 45 2

#sort -S 1G -T results/tmp results/$order/$order-candidates-1_$proc | uniq > results/$order/$order-candidates-b.sorted_$proc
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

