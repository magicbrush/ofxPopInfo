#pragma once

#include "ofMain.h"

namespace Lyu
{
  class ResizingCircleNode:
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
    ResizingCircleNode(
      float duration = 1.0f,
      float radius0 = 50.0f, 
      float radius1 = 3.0f,
      float lineWidth0 = 1.0f,
      float lineWidth1= 5.0f,
      ofColor cr0 = ofColor(0,255,0,0),
      ofColor cr1 = ofColor(0,255,0,255),
      WrapMode wmode = WrapMode::MIRRORED_REPEAT);

    virtual void customDraw();

    void reset();

  private:
    float TimeStart;
    float Duration;
    float Radius[2];
    float LineWidth[2];
    ofColor Cr[2];
    WrapMode WMode;



  };



}
