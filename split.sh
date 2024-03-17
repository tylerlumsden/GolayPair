order=$1
proc=$2

split --numeric-suffixes=1 --number=r/$proc results/$order-pairs-found results/$order-pairs-found-

for f in results/$order-pairs-found-*; do
   mv $f $(echo $f | sed -e 's/found-0*/found-/')
done