numproc=$1
for((i=0; i<numproc; i+=1)) do
echo "$i"
./build/debug/main "${@:2}" -n "${numproc}" -j ${i} --generate &
done

wait

echo Sorting
./build/debug/main "${@:2}" -n "${numproc}" --sort

echo Matching
./build/debug/main "${@:2}" --match



