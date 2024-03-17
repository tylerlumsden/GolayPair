<<<<<<< HEAD
#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=01-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%j.out # STDOUT
=======
#echo Matching Candidates
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

order=$1
len=$2
proc=$3

start=`date +%s`

<<<<<<< HEAD
sort -u -S 1G -T results/tmp results/$order/$order-candidates-0_$proc | uniq > results/$order/$order-candidates-a.sorted_$proc
sort -u -S 1G -T results/tmp results/$order/$order-candidates-1_$proc | uniq > results/$order/$order-candidates-b.sorted_$proc
=======
sort -u -S 1G -T results/$order results/$order/$order-candidates-0_$proc | uniq > results/$order/$order-candidates-a.sorted_$proc
sort -u -S 1G -T results/$order results/$order/$order-candidates-1_$proc | uniq > results/$order/$order-candidates-b.sorted_$proc
>>>>>>> 9e74f94e75d9464949a78554e178c43b165663af

#echo Sorting complete
#echo Matching

./bin/match_pairs $order $len $proc
end=`date +%s`

runtime2=$((end-start))
#echo $runtime2 seconds