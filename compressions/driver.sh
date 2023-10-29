
function handler() {
    echo "test"
}

trap handler SIGINT

gcc -Wall -g -O3 compress.72.b.1.c -lm -o b
gcc -Wall -g -O3 compress.72.a.1.c -lm -o a

start=`date +%s`

echo "Running a and b"

./b > compress.72.b.1.res &
./a > compress.72.a.1.res &

wait

end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds