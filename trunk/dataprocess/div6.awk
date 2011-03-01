#! /usr/bin/awk
# awk ' {t=$3-600; printf("%d %d %d %d \n",$1,$2,t,$3); }' 1.dat

BEGIN{
}
{
 t1=$3/600;
 t2=$4/600;
 printf("%d %d %d %d \n",$1,$2,t1,t2);
}
END{
}
