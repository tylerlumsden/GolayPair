#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=7-00:00
#SBATCH --mem-per-cpu=30G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report90/output.%a.out # STDOUT


./bin/filter_equivalent 64 32

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

