#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=01:00:00
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT
#SBATCH --array=1-50

order=64
len=32
cores=50

./split.sh 64 $cores

start=`date +%s`

    ./bin/filter_equivalent $order $len $SLURM_ARRAY_TASK_ID

end=`date +%s`

sort -u -S 1G -T results results/$order-unique-pairs-found-* | uniq > results/$order-unique-pairs-found

    runtime3=$((end-start))
    echo $runtime3 seconds

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*

