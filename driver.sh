#TO USE: ./driver.sh [ORDER] [Compression Factor] --[OPT1] [para1] --[OPT2] [para2]

order=$1
compress=$2

# added options & parameters

option1=$3
letter1=$4
option2=$5
letter2=$6

CYAN_COLOR='\033[1;36m'
NO_COLOR='\033[0m'

# input options

if [[ -z "$option1" || -z "$letter1" ]]; then
	option1=""
else
	option1="${option1#--}"
	letter1="${letter1^^}"

	if [[ -z "$option2" || -z "$letter2" ]]; then
		option2=""
	else
		option2="${option2#--}"
		letter2="${letter2^^}"
	fi
fi

# option1 tells start or not, option2 tells stop or not

if [ "$option1" = "stop" ]; then
	temp=$option1
	option1=$option2
	option2=$temp

	temp=$letter1
	letter1=$letter2
	letter2=$temp
fi

len=$(($order / $compress))

[ $order -eq $order 2>/dev/null ] || exit 1
[ $numproc -eq $numproc 2>/dev/null ] || exit 1

# ---------- Generation ---------- #
if [ -z "$option1" ]; then #start Generation (default)

option1=""

mkdir results 2> /dev/null
mkdir results/$order 2> /dev/null

echo Generating Candidates...

start=`date +%s`
./bin/generate_hybrid $order $compress
end=`date +%s`

runtime1=$((end-start))
echo $runtime1 seconds elapsed

fi #finish Generation

if [ "$option2" = "stop" ] && [ "$letter2" = "G" ];then
	echo -e "exit after finishing ${CYAN_COLOR}generation${NO_COLOR} ... GOODBYE!"
	exit 0
fi

# ---------- Matching ---------- #
if [[ -z "$option1" || ( "$option1" = "start" &&  "$letter1" = "M" ) ]];then #start Matching

option1=""

echo Matching Candidates...

start=`date +%s`

sort results/$order/$order-unique-filtered-a_1 | uniq > results/$order/$order-candidates-a.sorted_1
sort results/$order/$order-unique-filtered-b_1 | uniq > results/$order/$order-candidates-b.sorted_1

./bin/match_pairs $order $len 1
end=`date +%s`

runtime2=$((end-start))
echo $runtime2 seconds elapsed

mv results/$order/$order-pairs-found_1 results/$order/$order-pairs-found-1

total=$((runtime1 + runtime2))

echo $total seconds total

epochtime=$(date +%s)
datetime=$(date +"%Y-%m-%d")

cp results/$order/$order-pairs-found-1 results/history/$order-$compress-$datetime-$epochtime 2> /dev/null
cp results/$order/$order-pairs-found-1 results/$order-pairs-found 2> /dev/null

fi #finish Matching

if [ "$option2" = "stop" ] && [ "$letter2" = "M" ];then
	echo -e "exit after finishing ${CYAN_COLOR}matching${NO_COLOR} ... GOODBYE!"
	exit 0
fi

# ---------- Uncompression ---------- #
if [[ -z "$option1" || ( "$option1" = "start" &&  "$letter1" = "U" ) ]];then #start Uncompression

option1=""

if [ $compress -gt 1 ]
then

echo Uncompressing Pairs...

./uncompress.sh $order $compress 1 0

cp results/$order/$order-pairs-found-0 results/history/$order-1-$datetime-$epochtime 2> /dev/null
cp results/$order/$order-pairs-found-0 results/$order-pairs-found 2> /dev/null

rm results/$order/$order-pairs-found-0

else
	echo "compression factor = 1, no need to uncompress"

fi
fi #finish Matching

if [ "$option2" = "stop" ] && [ "$letter2" = "U" ];then
	echo -e "exit after finishing ${CYAN_COLOR}uncompression${NO_COLOR} ... GOODBYE!"
	exit 0
fi

# ---------- Equivalence Filtering ---------- #
if [[ -z "$option1" || ( "$option1" = "start" &&  "$letter1" = "E" ) ]];then #start Equivalence Filtering

echo Filtering Equivalences...

start=`date +%s`
./bin/cache_filter $order $order
end=`date +%s`

runtime3=$((end-start))

echo $runtime3 seconds elapsed

epochtime=$(date +%s)
datetime=$(date +"%Y-%m-%d")

cp results/$order-unique-pairs-found results/history/$order-1-$datetime-$epochtime 2> /dev/null

echo "Filtering Equivalences done, go see the results!"
fi #finish Equivalence Filtering
