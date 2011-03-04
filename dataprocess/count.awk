#! /usr/bin/awk
# awk ' {t=$3-600; printf("%d %d %d %d \n",$1,$2,t,$3); }' 1.dat

BEGIN{
c=0
}
{
a[$3]++
}
END{
for (j in a)
  print j,a[j]
}