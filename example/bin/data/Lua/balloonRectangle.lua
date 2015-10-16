----------------------------------------------------	
function draw()

	pts = {}	
	scnSize = math.sqrt(of.getWidth()*of.getHeight())		
	
	of.pushStyle()
	of.setColor(CrFill.r,CrFill.g,CrFill.b,CrFill.a)	
	of.fill()		
	of.beginShape()	
	for id=0,4,1 do	
		p = PL:getPointAtIndexInterpolated(id)	
		of.vertex(p)		
	end	
	of.endShape()		
	of.popStyle()
	
	of.pushStyle()
	of.setColor(CrEdge.r,CrEdge.g,CrEdge.b,CrEdge.a)	
	of.setLineWidth(EdgeWidth)	
	of.noFill()	
	of.beginShape()	
	for id=0,4,1 do		
		p = PL:getPointAtIndexInterpolated(id)	
		of.vertex(p)	
	end	
	of.endShape()		
	of.popStyle()	
	
end