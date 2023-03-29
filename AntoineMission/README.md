# RoboBot_Noah
This is a repository for the RoboBot Noah with mission for Robocup at DTU


### Short mission examples
#### forward calibration

thread=1
	vel=0,log=10.0:time=0.02
	vel=0.3:dist=1
	vel=0.0:time=0.1

#### turn calibration

thread=1
	vel=0,log=10.0:time=0.02
	vel=0.3,tr=0.2,label=1:turn=90
	vel=0.3:dist=0.2
	goto=1:count=3
	vel=0.0:time=0.1

#### Line sensor

thread=1
	log=10: time=0.05
	vel=0.2,acc=0.4,edger=0,white=1:dist=0.1,lv>5
	edger=0,white=1:dist=4,lv<5