----------------------------------------------------
function draw()
	pts = {}	
	ctr = of.Point;
	for id=0,4,1 do	
		pts[id] = PL:getPointAtIndexInterpolated(id);
		ctr = pts[id]
	end	
	ctr = ctr/4.0
	
	wd = pts[0]:distance(pts[1])
	ht = pts[1]:distance(pts[2])
			
	edge = math.max(wd,ht)	
	
	sx = wd/edge
	sy = ht/edge
	
	of.pushMatrix()
	of.pushStyle()
	of.fill()
	of.setColor(CrFill.r,CrFill.g,CrFill.b,CrFill.a)	
	of.setCircleResolution(36)
	of.scale(sx,sy,1)
	of.circle(0,0,edge)
	of.noFill()
	of.setColor(CrEdge.r,CrEdge.g,CrEdge.b,CrEdge.a)
	of.setLineWidth(EdgeWidth)	
	of.circle(0,0,edge)
	of.popStyle()
	of.popMatrix()	
	
end
