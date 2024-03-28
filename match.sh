#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=03-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%j.out # STDOUT

order=$1
len=$2
proc=$3

echo Sorting $order of length $len, file $proc

start=`date +%s`

sort -u -S 1G -T /home/lumsdent/scratch /home/lumsdent/scratch/$order-candidates-0_$proc | uniq > /home/lumsdent/scratch/$order-candidates-a.sorted_$proc
sort -u -S 1G -T /home/lumsdent/scratch /home/lumsdent/scratch/$order-candidates-1_$proc | uniq > /home/lumsdent/scratch/$order-candidates-b.sorted_$proc

#echo Sorting complete
#echo Matching

./bin/match_pairs $order $len $proc
end=`date +%s`

runtime2=$((end-start))
#echo $runtime2 seconds