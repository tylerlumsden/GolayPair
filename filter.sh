#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=01:00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT
#SBATCH --array=1-100

order=$1
len=$2
cores=$3

#./split.sh $order $cores

start=`date +%s`

./bin/filter_equivalent $order $len 1

sort -u -S 1G -T results results/$order-unique-pairs-found-* | uniq > results/$order-unique-pairs-found

end=`date +%s`

    runtime3=$((end-start))
    echo $runtime3 seconds

#cat ./results/$order/$order-pairs-found-* > results/$order/$order-pairs-found
#rm ./results/$order/$order-pairs-found-*
