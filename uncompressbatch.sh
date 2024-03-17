#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=07-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT
#SBATCH --array=1-14

<<<<<<< HEAD
order=$1
compress=$2
newcompress=$3
cores=$4
=======
cores=14

order=90
compress=6
newcompress=2
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

############################################### INPUT ABOVE
make

mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

./split.sh $order $cores

sbatch --array=1-$cores uncompress.sh $order $compress $newcompress

wait



<<<<<<< HEAD

=======
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af
