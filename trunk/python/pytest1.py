
#!/usr/bin/env python
# usage: python gen_markov_trace.py <number-of-nodes> <run-time [s]> <output-file>

import sys
import datetime
import os
import operator
import array
import random

if len(sys.argv) != 2:
    print "usage: python " + sys.argv[0] + " <scenario> "
    sys.exit(1)

scenarioNum=int(sys.argv[1])-1

#sendMode = str(sys.argv[1])
#interest = str(sys.argv[2])
#filePath = str(sys.argv[3])

userName="user"

application="sndbyinterest"
parameters="-s -i -f"
para_s=" -s "
para_i=" -i "
para_f=" -f ~/.Haggle/test.txt"

#CAM 4 commmunity
commNum=4
comm=[[11 ,29],
[3 ,32 ,7 ,28 ,16 ,34 ,36 ,22 ,21 ,25 ,27 ,12 ,8],
[1 ,4 ,30 ,2 ,14 ,18 ,23 ,17 ],
[5 ,15 ,19 ,33 ,20 ,10 ,6 ,13 ,9 ,24 ,26 ,35 ,31]]

#newman
#commNum=4
#comm=[[1, 2, 4, 5, 6, 9, 10, 13, 14, 15, 17, 18, 19, 20, 23, 30, 33],
#[3, 11, 22, 25, 27, 29, 34, 36, 7, 8, 12, 16, 21, 28, 32],
#[24, 26, 35],
#[31]]

#Kclique
#commNum=2
#comm=[[1, 12, 18, 20, 4, 5, 10, 6, 15, 17, 19, 2, 23, 33],
#[11, 21, 36, 12, 25, 28, 3, 34, 7, 16, 22, 27, 32]]

#Eiko Paper
#commNum=2
#comm1=[[11 ,29 ,3 ,32 ,7 ,28 ,16 ,34 ,36 ,22 ,21 ,25 ,27 ,12 ,8],
#[1 ,4 ,30 ,2 ,14 ,18 ,23 ,17 ,5 ,15 ,19 ,33 ,20 ,10 ,6 ,13 ,9 ,24 ,26 ,35 ,31]]

debug=1

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

for x in range(commNum):
	
	communityID=x+1
	#fileName=localName+str(x+1)+".xml"
	
	#print intrasub[0][x]
	
	cmd=" \"screen -dmS "+application+" "+application
	
	#cmd_send=cmd+para_s+str(communityID)+para_i+str(communityID)+para_f+"\""
	
	cmd_send=cmd+para_s+listin[scenarioNum][0][x]+para_i+listin[scenarioNum][1][x]+para_f+"\""

		
	if debug==1:
		print comm[x]
		#print fileName
	for i in comm[x]:
		#print i
		node_name="node-"+str(i)
		#cmd_mkdir="ssh "+userName+"@"+node_name+" mkdir .Haggle"
		#cmd_mkscp="scp "+fileName+" "+userName+"@"+node_name+":.Haggle/"+remoteName
		
		 #ssh $NODE_USERNAME@$node_name "screen -dmS $application $application $parameters"
		#cmd_run_app="ssh "+userName+"@"+node_name+" screen -dmS "+application+" "+application+" "+parameters
		
		cmd_run_app="ssh "+userName+"@"+node_name+cmd_send
		
		if debug ==1:
			#print node_name
			print cmd_run_app
		#os.system(cmd_run_app)

#print "--"
