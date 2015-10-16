#pragma once

#include "ofMain.h"

namespace Lyu
{
  class ArcBarNode:
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
    ArcBarNode(
      float duration = 1.0f,
      float radius0 = 50.0f, 
      float radius1 = 60.0f, 
      float startPct = 1.0f,
      ofColor cr = ofColor(0,255,0,255),     
      WrapMode wmode = WrapMode::MIRRORED_REPEAT,
      int circleRes = 36.0f);
    virtual void customDraw();
    void reset();

  private:
    float TimeStart;
    float Duration;
    float Radius[2];
    ofColor Cr;
    WrapMode WMode;
    int CircleRes;
    float StartPct;
  };



}
