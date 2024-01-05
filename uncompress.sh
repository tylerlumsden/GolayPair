    
    order=$1
    newcompress=$2
    

    start=`date +%s`

    echo Uncompressing

    rm results/$order-unique-filtered-0
    rm results/$order-unique-filtered-1

    linecount=$(wc -l < results/$order-pairs-found)

    for ((i = 1; i<=$linecount; i++))
    do
        echo line $i
        ./bin/uncompression $i $newcompress
    done

    end=`date +%s`
    runtime3=$((end-start))
    echo $runtime3 seconds

    sed -i -E "s/#define COMPRESS [[:digit:]]+/#define COMPRESS $newcompress/" lib/golay.h
    make ORDER="$order" COMPRESS=$newcompress

    sort results/$order-unique-filtered-0 | uniq > results/$order-candidates-a.sorted
    sort results/$order-unique-filtered-1 | uniq > results/$order-candidates-b.sorted

    total=$((runtime1 + runtime2 + runtime3))

    ./match.sh $order

    uncompressedpairs=$(wc -l < results/$order-pairs-found)