    make
    
    order=$1
    compress=$2
    newcompress=$3
    

    start=`date +%s`

    echo Uncompressing

    rm results/$order-unique-filtered-0
    rm results/$order-unique-filtered-1

    linecount=$(wc -l < results/$order-pairs-found)

    for ((i = 1; i<=$linecount; i++))
    do
        echo line $i
        ./bin/uncompression $i $order $compress $newcompress
    done

    end=`date +%s`
    runtime3=$((end-start))
    echo $runtime3 seconds

    sort results/$order-unique-filtered-0 | uniq > results/$order-candidates-a.sorted
    sort results/$order-unique-filtered-1 | uniq > results/$order-candidates-b.sorted

    total=$((runtime1 + runtime2 + runtime3))

    ./match.sh $order $(($order / $newcompress))

    if [ $newcompress -gt 1 ]
    then
    ./bin/filter_equivalent $order $(($order / $newcompress))
    rm results/$order-pairs-found
    mv results/$order-unique-pairs-found results/$order-pairs-found
    fi

    uncompressedpairs=$(wc -l < results/$order-pairs-found)