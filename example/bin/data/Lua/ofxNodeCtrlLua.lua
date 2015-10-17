
-- Input -------------------------------------------
Position0 = {} -- the initial position
Scale0 = {} -- the initial scale
Orientation0 = {} -- the initial orientation quaternion
Position = {} -- the ofNode's position
Scale = {} -- the ofNode's scale
Orientation = {} -- the ofNode's orientation quaternion
Speed = 1.0 -- the global speed

-- Parameters --------------------------------------
-- screen size
scnSize = math.sqrt(of.getWidth()*of.getHeight())

------------------- Functions ----------------------
----------------------------------------------------
-- zoomInOut zoom in/out 
function zoomInOut()	
	tNow = of.getElapsedTimef()
	S = 0.2*math.sin(tNow*Speed*10)+1.0
	Scale[1] = S*Scale0[1];
	Scale[2] = S*Scale0[2];
	Scale[3] = Scale0[3];
end

----------------------------------------------------
-- ascend: move up toward the top
function ascend()
	dt = of.getLastFrameTime()
	dy = -scnSize*dt*Speed*0.3
	Position[2] = Position[2]+dy	
end

----------------------------------------------------
-- rolling: rolling around
function rolling()
	tNow = of.getElapsedTimef()
	tNowS = tNow*Speed*360
	
	degrees = of.wrap(tNowS,0,360)	
	Q = of.Quaternion(Orientation[1],Orientation[2],Orientation[3],Orientation[4])
	Q:makeRotate(degrees,0,0,1)
	
	QV = Q:asVec4()	
	Orientation[1] = QV.x
	Orientation[2] = QV.y
	Orientation[3] = QV.z
	Orientation[4] = QV.w	
end

----------------------------------------------------
-- trembling
function trembling()
	tNow = of.getElapsedTimef()
	tNowS = tNow*Speed*10
	
	degrees = 40.0*of.noise(of.random(0.9,1.1)*tNowS)-20.0	
	Q = of.Quaternion(Orientation[1],Orientation[2],Orientation[3],Orientation[4])
	Q:makeRotate(degrees,0,0,1)	
	QV = Q:asVec4()	
	Orientation[1] = QV.x
	Orientation[2] = QV.y
	Orientation[3] = QV.z
	Orientation[4] = QV.w

	S = 0.9*of.noise(of.random(0.9,1.1)*tNowS)+0.8
	Scale[1] = S*Scale0[1];
	Scale[2] = S*Scale0[2];
	Scale[3] = Scale0[3];
end

----------------------------------------------------
-- shakingAround
function shakingAround()
	tNow = of.getElapsedTimef()
	tNowS = tNow*Speed*10
	
	degrees = 10.0*of.noise(of.random(0.9,1.1)*tNowS)-5.0	
	Q = of.Quaternion(Orientation[1],Orientation[2],Orientation[3],Orientation[4])
	Q:makeRotate(degrees,0,0,1)	
	QV = Q:asVec4()	
	Orientation[1] = QV.x
	Orientation[2] = QV.y
	Orientation[3] = QV.z
	Orientation[4] = QV.w

	--S = 0.9*of.noise(1.0323457*tNowS)+0.8
	--Scale[1] = S
	--Scale[2] = S
	--Scale[3] = 1.0
	
	shakeMax = scnSize*0.03
	dx = (of.noise(of.random(0.9,1.1)*tNowS)-0.5)*shakeMax
	dy = (of.noise(of.random(0.9,1.1)*tNowS)-0.5)*shakeMax
	Position[1] = Position0[1] + dx;
	Position[2] = Position0[2] + dy;	
end