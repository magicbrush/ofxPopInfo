#include "ResizingCircleNode.h"

Lyu::ResizingCircleNode::ResizingCircleNode( 
  float duration /*= 1.0f*/, 
  float radius0 /*= 50.0f*/, 
  float radius1 /*= 3.0f*/, 
  float lineWidth0 /*= 1.0f*/, 
  float lineWidth1/*= 5.0f*/, 
  ofColor cr0 /*= ofColor(0,255,0,0)*/, 
  ofColor cr1 /*= ofColor(0,255,0,255)*/, 
  WrapMode wmode /*= WrapMode::MIRRORED_REPEAT*/ ):
  TimeStart(-1.0f),
  Duration(duration),
  WMode(wmode)
{
  Radius[0] = radius0;
  Radius[1] = radius1;
  LineWidth[0] = lineWidth0;
  LineWidth[1] = lineWidth1;
  Cr[0] = cr0;
  Cr[1] = cr1;
}

void Lyu::ResizingCircleNode::customDraw()
{
  if(TimeStart<=0)
  {
    TimeStart = ofGetElapsedTimef();
    return;
  }

  float TimeNow = ofGetElapsedTimef();
  float PassedTime = TimeNow-TimeStart;
  float TimeNorm = PassedTime/Duration;
  float pct(0);
  if(WMode==WrapMode::CLAMP)
  {
    pct = ofClamp(TimeNorm,0,1);
  }
  else if(WMode==WrapMode::REPEAT)
  {
    pct = ofWrap(TimeNorm,0,1);
  }
  else if(WMode==WrapMode::MIRRORED_REPEAT)
  {
    pct = ofWrap(TimeNorm,0,2);
    pct = pct>1.0f?2.0f-pct:pct;
  }

  float radius = pct*Radius[0] + (1.0f-pct)*Radius[1];
  float lineWd = pct*LineWidth[0] + (1.0f-pct)*LineWidth[1];
  ofColor cr;
  for(int i=0;i<4;i++)
  {
    cr[i] = pct*Cr[0][i] + (1.0f-pct)*Cr[1][i];
  }

  ofPushStyle();
  ofNoFill();
  ofSetColor(cr);
  ofSetLineWidth(lineWd);
  ofCircle(ofVec3f(0,0,0),radius);
  ofPopStyle();
}

void Lyu::ResizingCircleNode::reset()
{
  TimeStart = -1.0f;
}

