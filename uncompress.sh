#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=7-00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT 
    
    make
    
    order=$1
    compress=$2
    newcompress=$3
    proc=$SLURM_ARRAY_TASK_ID
    
    start=`date +%s`

    echo Uncompressing

    linecount=$(wc -l < results/$order-pairs-found-$proc)

    for ((i = 1; i<=$linecount; i++))
    do
        echo line $i
        ./bin/uncompression $i $proc $order $compress $newcompress

        ./match.sh $order $(($order / $newcompress)) $proc $i

        cat results/$order/$order-pairs-found_$proc >> results/$order/$order-pairs-found-$proc

    done

    end=`date +%s`
    runtime3=$((end-start))
    echo $runtime3 seconds

    total=$((runtime1 + runtime2 + runtime3))