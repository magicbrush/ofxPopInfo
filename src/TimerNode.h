#pragma once

#include "ofMain.h"

namespace Lyu
{
  class TimerNode:
    public ofNode
  {
  public:
    enum class WrapMode
    {
      CLAMP,
      REPEAT,
      MIRRORED_REPEAT
    };

  public:
    static ofPtr<TimerNode> createTimer(
      ofVec3f Pos,
      ofVec3f Scale = ofVec3f(1,1,1),      
      ofTrueTypeFont* font=nullptr,
      float duration = 1.0f,      
      float startPct = 1.0f,      
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black,  
      int numberPrecision = 2,
      WrapMode wmode = WrapMode::MIRRORED_REPEAT,
      ofQuaternion Orientation = ofQuaternion());
    static ofPtr<TimerNode> createCounter(
      float startValue,
      float endValue,
      ofVec3f Pos,
      ofVec3f Scale = ofVec3f(1,1,1),      
      ofTrueTypeFont* font=nullptr,
      float duration = 1.0f,      
      float startPct = 1.0f,      
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black,
      int numberPrecision = 2,
      WrapMode wmode = WrapMode::MIRRORED_REPEAT,
      ofQuaternion Orientation = ofQuaternion());

  public:
    TimerNode(
      float startValue,
      float endValue,
      ofTrueTypeFont* font=nullptr,
      float duration = 1.0f,      
      float startPct = 1.0f,      
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black, 
      int numberPrecision = 2,
      WrapMode wmode = WrapMode::MIRRORED_REPEAT);
    TimerNode(
      ofTrueTypeFont* font=nullptr,
      float duration = 1.0f,      
      float startPct = 1.0f,      
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black,  
      int numberPrecision = 2,
      WrapMode wmode = WrapMode::MIRRORED_REPEAT);
    void init( 
      float startValue, 
      float endValue, 
      ofTrueTypeFont* font, 
      float duration, 
      float edgeWidth, 
      ofColor crFill, 
      ofColor crEdge,
      float startPct,
      int NumberPrecision,
      WrapMode wmode);

    virtual void customDraw();
    void reset();

  private:
    ofTrueTypeFont* pFont;
    float TimeStart;
    float Duration; 
    float StartValue,EndValue;
    float EdgeWidth;
    ofColor CrFill,CrEdge;
    int NumberPrecision;
    WrapMode WMode;    
    float StartPct;
  };



}
