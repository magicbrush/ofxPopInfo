#include "TimerNode.h"
#include "LyuUtils.h"


ofPtr<Lyu::TimerNode> Lyu::TimerNode::createTimer( 
  ofVec3f Pos, 
  ofVec3f Scale /*= ofVec3f(1,1,1)*/,
  ofTrueTypeFont* font/*=nullptr*/, 
  float duration /*= 1.0f*/, 
  float startPct /*= 1.0f*/, 
  ofColor crFill /*= ofColor::white*/,
  float edgeWidth /*= 0.0f*/, 
  ofColor crEdge /*= ofColor::black*/, 
  int numberPrecision,
  WrapMode wmode /*= WrapMode::MIRRORED_REPEAT*/, 
  ofQuaternion Orientation /*= ofQuaternion()*/ )
{
  ofPtr<Lyu::TimerNode> TN;
  TN.reset(new Lyu::TimerNode(
    font,
    duration,
    startPct,
    crFill,
    edgeWidth,
    crEdge,    
    numberPrecision,
    wmode)); 
  TN->setGlobalPosition(Pos);
  TN->setScale(Scale);
  TN->setGlobalOrientation(Orientation);
  return TN;
}

ofPtr<Lyu::TimerNode> Lyu::TimerNode::createCounter( 
  float startValue, 
  float endValue, 
  ofVec3f Pos, 
  ofVec3f Scale /*= ofVec3f(1,1,1)*/, 
  ofTrueTypeFont* font/*=nullptr*/, 
  float duration /*= 1.0f*/, 
  float startPct /*= 1.0f*/, 
  ofColor crFill /*= ofColor::white*/, 
  float edgeWidth /*= 0.0f*/, 
  ofColor crEdge /*= ofColor::black*/,
  int numberPrecision,
  WrapMode wmode /*= WrapMode::MIRRORED_REPEAT*/, 
  ofQuaternion Orientation /*= ofQuaternion()*/ )
{
  ofPtr<Lyu::TimerNode> TN;
  TN.reset(new Lyu::TimerNode(
    startValue,
    endValue,
    font,
    duration,
    startPct,
    crFill,
    edgeWidth,
    crEdge,    
    numberPrecision,
    wmode)); 
  TN->setGlobalPosition(Pos);
  TN->setScale(Scale);
  TN->setGlobalOrientation(Orientation);
  return TN;
}

Lyu::TimerNode::TimerNode( 
  float startValue,
  float endValue,
  ofTrueTypeFont* font, 
  float duration /*= 1.0f*/, 
  float startPct /*= 1.0f*/, 
  ofColor crFill /*= ofColor::white*/, 
  float edgeWidth /*= 0.0f*/, ofColor 
  crEdge /*= ofColor::black*/, 
  int numberPrecision,
  WrapMode wmode /*= WrapMode::CLAMP*/ )
{
  init(
    startValue, 
    endValue, 
    font, 
    duration, 
    edgeWidth, 
    crFill, 
    crEdge, 
    startPct,
    numberPrecision,
    wmode);

}

Lyu::TimerNode::TimerNode( 
  ofTrueTypeFont* font/*=nullptr*/, 
  float duration /*= 1.0f*/, 
  float startPct /*= 1.0f*/, 
  ofColor crFill /*= ofColor::white*/, 
  float edgeWidth /*= 0.0f*/, 
  ofColor crEdge /*= ofColor::black*/, 
  int numberPrecision,
  WrapMode wmode /*= WrapMode::MIRRORED_REPEAT*/ )
{
  init(0,0,
    font,
    duration,
    edgeWidth,
    crFill,
    crEdge,
    startPct,
    numberPrecision,
    wmode);
}

void Lyu::TimerNode::init( 
  float startValue, 
  float endValue, 
  ofTrueTypeFont* font, 
  float duration, 
  float edgeWidth, 
  ofColor crFill, 
  ofColor crEdge, 
  float startPct,
  int numberPrecision,
  WrapMode wmode)
{
  StartValue=startValue;
  EndValue=endValue;
  pFont=font;
  TimeStart=-1;
  Duration=duration;
  EdgeWidth=edgeWidth;
  CrFill=crFill;
  CrEdge=crEdge;
  StartPct=startPct;
  if(StartValue==EndValue)
  {
    EndValue = StartValue+Duration;
  }
  NumberPrecision= numberPrecision;
  WMode = wmode;
}

void Lyu::TimerNode::customDraw()
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

  float Value = pct*StartValue+(1.0f-pct)*EndValue;

  stringstream ss;
  ss << setprecision(NumberPrecision) << setiosflags(ios::fixed) << Value;
    
  ofPushStyle();
  if(pFont==nullptr)
  {
    ofDrawBitmapStringHighlight(
      ss.str(),0,0,CrEdge,CrFill);      
  }
  else
  {      
    ofSetColor(CrFill);
    Lyu::drawTxtByFontAt(
      ss.str(),pFont,ofVec2f(0,0),ofVec2f(1,1));
    if(EdgeWidth>0.0)
    {
      ofSetColor(CrEdge);
      Lyu::drawTxtByFontAt(
        ss.str(),pFont,ofVec2f(0,0),ofVec2f(1,1),EdgeWidth);
    }            
  }    
  ofPopStyle();
}

void Lyu::TimerNode::reset()
{
  TimeStart = -1.0f;
}
