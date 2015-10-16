#pragma once

#include "ofMain.h"

namespace Lyu
{
  class TextNode:
    public ofNode
  {
  public:
    static ofPtr<TextNode> create(
      string msg,
      ofTrueTypeFont* font=nullptr,
      ofVec3f Pos=ofVec2f(
        ofGetWidth()/2,ofGetHeight()/2),      
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black,
      ofVec2f Scal = ofVec2f(1,1),
      ofQuaternion Orin = ofQuaternion());
      
      ofRectangle getTextRect();

  public:
    TextNode(
      string msg,
      ofTrueTypeFont* font=nullptr,
      ofColor crFill = ofColor::white,
      float edgeWidth = 0.0f,
      ofColor crEdge = ofColor::black);
    virtual void customDraw() override;

  private:
    string Msg;
    ofTrueTypeFont* f;
    float EdgeWidth;
    ofColor CrFill,CrEdge;
  };
}
