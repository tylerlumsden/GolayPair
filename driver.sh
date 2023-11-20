#!/bin/bash
#SBATCH --account=def-cbright
#SBATCH --time=0-00:15
#SBATCH --mem-per-cpu=2G
#SBATCH --cpus-per-task=2

#TO USE: ./driver.sh [ORDER] [LEN] [Number of parallel divisions] [File to read from] [Line number for sequence] [Flag (0 or 1)]

order=$1
len=$2
numproc=$3


[ $order -eq $order 2>/dev/null ] || exit 1
[ $numproc -eq $numproc 2>/dev/null ] || exit 1


sed -i -E "s/#define ORDER [[:digit:]]+/#define ORDER $len/" lib/golay.h
#sed -i "1s/.*/#define LEN $order/" ../golay.h

make ORDER="$len" LEN="$order"

echo Number of processes: $numproc

start=`date +%s`

for ((i = 0; i<$numproc; i++))
do  
    echo i: $i
    ./bin/generate_orderly $flag $i $numproc $file $line &
done

wait

end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds
