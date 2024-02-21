#!/bin/bash
#SBATCH --account=rrg-cbright
#SBATCH --time=01:00:00
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=1
#SBATCH -o ./Report/output.%a.out # STDOUT 
    
    make

    proc=1
    
    order=$1
    compress=$2
    newcompress=$3
    
    start=`date +%s`

    echo Uncompressing

    linecount=$(wc -l < results/$order-pairs-found-1)

    for ((i = 1; i<=$linecount; i++))
    do
        echo line $i
        ./bin/uncompression $i 1 $order $compress $newcompress

        #./match.sh $order $(($order / $newcompress)) $proc $i

        #cat results/$order/$order-pairs-found_$proc >> results/$order/$order-pairs-found-$proc

    done

    end=`date +%s`
    runtime3=$((end-start))
    echo $runtime3 seconds

    total=$((runtime1 + runtime2 + runtime3))