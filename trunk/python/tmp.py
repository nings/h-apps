#intra sub
i1=[["c1","c2","c3","c4"],
["c1","c2","c3","c4"]]
#intra top
i2=[["c1","c1","c3","c3"],
["c1","c1","c3","c3"]]
#inter sub
i3=[["c1","c2","c3","c4"],
["c2","c1","c4","c3"]]
#inter top
i4=[["c1","c1","c3","c3"],
["c3","c3","c1","c1"]]
#inter cross
i5=[["c1","c2","c3","c4"],
["c5","c6","c1","c1"]]

i6=[["c2","c1","c3","c4"],
["c5","c6","c1","c1"]]

i7=[["c2","c3","c1","c4"],
["c1","c1","c5","c6"]]

i8=[["c2","c3","c4","c1"],
["c1","c1","c5","c6"]]


listin=[i1,i2,i3,i4,i5,i6,i7,i8]

print listin[0][0][0]

for x in range(1,4):
	t=i+str(x)
	print t 
	#print x