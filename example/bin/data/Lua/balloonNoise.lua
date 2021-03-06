----------------------------------------------------
function draw()
	pts = {}	
	length = 0	
	for i =1,4,1 do
		pt0 = PL:getPointAtIndexInterpolated(i-1)		
		pt = PL:getPointAtIndexInterpolated(i)		
		D = pt0:distance(pt)		
		length = length + D		
	end
	
	scnSize = math.sqrt(of.getWidth()*of.getHeight())
		
	maxid = 100*length/scnSize +4;	
	for id=0,maxid,1 do	
		pts[id] = PL:getPointAtIndexInterpolated(id*4/maxid)			
	end	
	
	ZigSize = scnSize/300;
	xrand = {}
	yrand = {}
	for id =0,maxid,1 do	
		xrand[id] = of.random(-ZigSize,ZigSize)
		yrand[id] = of.random(-ZigSize,ZigSize)		
	end
	
	of.pushStyle()
	of.setColor(CrFill.r,CrFill.g,CrFill.b,CrFill.a)	
	of.fill()		
	of.beginShape()	
	for id=0,maxid,1 do	
		p = pts[id];
		p.x = p.x + xrand[id]
		p.y = p.y + yrand[id]
		of.vertex(p)	
	end	
	of.endShape()		
	of.popStyle()
	
	of.pushStyle()
	of.setColor(CrEdge.r,CrEdge.g,CrEdge.b,CrEdge.a)	
	of.setLineWidth(EdgeWidth)	
	of.noFill()	
	of.beginShape()	
	for id=0,maxid,1 do	
		p = pts[id];
		p.x = p.x + xrand[id]
		p.y = p.y + yrand[id]
		of.vertex(p)	
	end	
	of.endShape()	
	
	of.popStyle()	
end
