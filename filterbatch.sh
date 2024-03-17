#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=01:00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT
#SBATCH --array=1-100

order=$1
len=$2


./bin/filter_equivalent $order $len $SLURM_ARRAY_TASK_ID