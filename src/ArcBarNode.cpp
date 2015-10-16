#include "ArcBarNode.h"

Lyu::ArcBarNode::ArcBarNode( 
  float duration /*= 1.0f*/, 
  float radius0 /*= 50.0f*/, 
  float radius1 /*= 3.0f*/,  
  float startPct,
  ofColor cr /*= ofColor(0,255,0,0)*/,  
  WrapMode wmode /*= WrapMode::MIRRORED_REPEAT*/,
  int circleRes):
  TimeStart(-1.0f),
  Duration(duration),
  WMode(wmode),
  CircleRes(circleRes),
  StartPct(startPct)
{
  Radius[0] = radius0;
  Radius[1] = radius1;  
  Cr = cr;
}

void Lyu::ArcBarNode::customDraw()
{
  if(TimeStart<=0)
  {
    TimeStart = ofGetElapsedTimef();
    return;
  }

  float TimeNow = ofGetElapsedTimef();
  float PassedTime = TimeNow-TimeStart;
  float TimeNorm = StartPct+PassedTime/Duration;
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
  
  float deg = pct*360.0f;  
  
  ofPath P;
  
  float degStep = 360.0f/CircleRes;

  int IterNum = ceil(deg/degStep);
  float degStep2 = deg/IterNum;
  for(int i=0;i<=IterNum;i++)
  {
    float rad = ofDegToRad(degStep2*i);
    float x = Radius[0]*cos(rad);
    float y = Radius[0]*sin(rad);
    P.lineTo(ofVec2f(x,y));
  }  
  for(int i=IterNum;i>=0;i--)
  {
    float rad = ofDegToRad(degStep2*i);
    float x = Radius[1]*cos(rad);
    float y = Radius[1]*sin(rad);
    P.lineTo(ofVec2f(x,y));
  }
  P.lineTo(ofVec2f(Radius[0],0));
  P.setColor(Cr);

  ofPushStyle();
  ofFill();
  P.draw();  
  ofPopStyle();
}

void Lyu::ArcBarNode::reset()
{
  TimeStart = -1.0f;
}

