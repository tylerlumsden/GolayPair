
sed -f sedChanges1 PG72.sols > PG72.sols.seded
awk '{for (i=1;i<=NF;i++) if (i>=4 ) printf("%s ", $i); print ""}' PG72.sols.seded > PG72.awk
sed -f sedChanges2 PG72.awk > PG72.awk.seded

