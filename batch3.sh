#!/bin/bash
<<<<<<< HEAD
#SBATCH --account=def-cbright
#SBATCH --time=7-00:00
#SBATCH --mem-per-cpu=2G
=======
#SBATCH --account=rrg-cbright
#SBATCH --time=1-00:00
#SBATCH --mem-per-cpu=4G
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%a.out # STDOUT

order=90
compress=6
newcompress=2

############################################### INPUT ABOVE
<<<<<<< HEAD
make

mkdir ./results/$order

linecount=$(wc -l < results/$order-pairs-found)

./split.sh 90 3

./bin/uncompression 670903 3 $order $compress $newcompress

wait
=======
#make

#mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

sed -n '670905p' results/$order-pairs-found > results/$order-pairs-found-3

./bin/uncompression 1 3 $order $compress $newcompress

#wait

./match.sh 90 45 3
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

<<<<<<< HEAD

=======
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af
