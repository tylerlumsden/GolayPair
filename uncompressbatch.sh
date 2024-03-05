#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=07-00:00
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT
#SBATCH --array=1-997

cores=997

order=64
compress=2
newcompress=1

############################################### INPUT ABOVE
make

mkdir ./results/$order

#linecount=$(wc -l < results/$order-pairs-found)

./split.sh $order $cores

sbatch --array=1-$cores uncompress.sh $order $compress $newcompress

wait



