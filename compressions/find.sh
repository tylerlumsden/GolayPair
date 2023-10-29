
   awk '{print $1}' compress.72.a.1.res | sort -u > compress.72.a.1.res.sorted

   awk '{print $1}' compress.72.b.1.res | sort -u > compress.72.b.1.res.sorted

   comm -1 -2 compress.72.a.1.res.sorted compress.72.b.1.res.sorted

