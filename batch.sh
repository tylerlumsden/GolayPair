#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=1-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%j.out # STDOUT

sort -u -S 1G -T results results/68-unique-pairs-found-* | uniq > results/68-unique-pairs-found

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

