#pragma once

#include "ofMain.h"
#include "Informer.h"
#include "TextNode.h"

class ofxLua;
namespace Lyu
{
  class TextNode;
  class BalloonNode:
    public ofNode
  {
  public:
    static ofPtr<BalloonNode> create(
      ofPtr<TextNode> TxtN,          
      ofColor crFill = ofColor::white,
      float edgeWidth = 2.0f,
      ofColor crEdge = ofColor::black,
      ofVec2f Scal = ofVec2f(1.2,1.2));

  public:
    BalloonNode(
      float width, 
      float height,
      float edgeWidth=2.2f,
      ofColor edgeColor=ofColor::black,
      ofColor fillColor=ofColor::white);
    ~BalloonNode();
    void loadLuaScript(
      string luaPath,     
      string drawFcn = "draw"  
      );

    virtual void customDraw();

  private:
    void resetLuaBalloonParams();
    void initLua();

  private:
    ofRectangle R;
    float EdgeWidth;
    ofColor CrEdge,CrFill;    

    string DrawFcn,Pref;
    static ofPtr<ofxLua> L;
    string LuaPath;
    vector<float> R_vertices;
    static string 
      ExitScript,
      LuaRectParamsInitScript;
  }; 

}

