
-- Input -------------------------------------------
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
	Scale[1] = S
	Scale[2] = S
	Scale[3] = 1.0	
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
	
	degrees = 40.0*of.noise(tNowS)-20.0	
	Q = of.Quaternion(Orientation[1],Orientation[2],Orientation[3],Orientation[4])
	Q:makeRotate(degrees,0,0,1)	
	QV = Q:asVec4()	
	Orientation[1] = QV.x
	Orientation[2] = QV.y
	Orientation[3] = QV.z
	Orientation[4] = QV.w

	S = 0.9*of.noise(1.0323457*tNowS)+0.8
	Scale[1] = S
	Scale[2] = S
	Scale[3] = 1.0
end

----------------------------------------------------
-- shaking
function shaking()
	tNow = of.getElapsedTimef()
	tNowS = tNow*Speed*10
	
	degrees = 40.0*of.noise(tNowS)-20.0	
	Q = of.Quaternion(Orientation[1],Orientation[2],Orientation[3],Orientation[4])
	Q:makeRotate(degrees,0,0,1)	
	QV = Q:asVec4()	
	Orientation[1] = QV.x
	Orientation[2] = QV.y
	Orientation[3] = QV.z
	Orientation[4] = QV.w

	S = 0.9*of.noise(1.0323457*tNowS)+0.8
	Scale[1] = S
	Scale[2] = S
	Scale[3] = 1.0
end