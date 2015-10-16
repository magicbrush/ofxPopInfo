//dependence: ofxAsset
#pragma once

#include "ofMain.h"
#include "SingletonTemplate.h"
#include "TextNode.h"
#include "BalloonNode.h"
#include "ResizingCircleNode.h"
#include "ofxNodeCtrlLua.h"
#include "ofxAssets.h"
#define INFORMER (Lyu::singleton<Lyu::Informer>::instance())

namespace Lyu
{
  class ofxNodeController;
  class Informer:
    public ofBaseUpdates,
    public ofBaseDraws
  {
  public:
    struct InfoStruct
    {
      ofPtr<ofNode> iNode;
      float delay;
      float duration;
      float speed;
    };
    struct NodeCtrlStruct
    {
      ofPtr<ofxNodeController> NCtrl;
      ofPtr<ofNode> NTgt;
      float delay;
      float duration;
      float speed;
    };

  public:
    Informer();
    ~Informer();

    void pushInfo(ofPtr<ofNode> Info, 
      float duration = 1.0f,
      float delay = 0.0f,
      float zOrder = 0.0f,
      float speed = 1.0f,
      ofPtr<ofxNodeController> nCtrl = ofPtr<ofxNodeController>());
    void removeInfo(ofPtr<ofNode> Info);
    void removeInfo(float zOrder);
    void changeDuration(ofPtr<ofNode> Info,
      float duration);
    void changeSpeed(ofPtr<ofNode> Info,
      float speed);
    void changeZOrder(ofPtr<ofNode> Info,
      float zOrder);
    void changeDelay(ofPtr<ofNode> Info,
      float delay);
    void changeInfo(ofPtr<ofNode> Info,
      float duration,
      float delay,
      float zOrder,
      float speed);
    InfoStruct getInfo(ofPtr<ofNode> Info);

    void pushNodeCtrl(
      ofPtr<ofxNodeController> nCtrl,
      ofPtr<ofNode> nTgt,
      float duration = 1.0f,
      float delay = 0.0f,      
      float speed = 1.0f);

    void update() final; 
    void draw( float x = 0, float y = 0 ) final;
    void clear();

  private:
    void updateNodeCtrls( float dt );
    void updateINodes( float dt );
    virtual void draw( 
      float x, float y, float w, float h ) final;
    virtual float getHeight() final;
    virtual float getWidth() final;
    
  private:
    map<float,InfoStruct> I;
    vector<NodeCtrlStruct> C;

    float timeLast;
  };

  template<typename T>
  ofPtr<ofNode> pushInfo(
    T msg,
    ofVec2f pos, 
    float duration = 0.618f,
    float delay = 0.0f,
    float zOrder = 0.0f,
    string fontName="vag",
    float FontSize=18.0f,
    ofVec2f Scale = ofVec2f(1.0f,1.0f),
    ofColor CrFill = ofColor::white,
    float edgeSize = 1.0f,
    ofColor CrEdge = ofColor::black
    )
  {
    {  
      ofPtr<TextNode> TN= 
        TextNode::create(
        ofToString(msg),
        &ofxAssets::font(fontName,FontSize),
        pos,
        CrFill,
        edgeSize,
        CrEdge);
      TN->setScale(Scale);
      INFORMER.pushInfo(TN,duration,delay,zOrder);
      return TN;
    }
  }

  template<typename T>
  ofPtr<ofNode> pushInfoWithLuaCtrl(
    T msg,    
    ofVec2f pos,
    string LuaScriptPath = "Lua\\ofxNodeCtrlLua.lua",
    string LuaFcnName = "zoomInOut",
    float duration = 0.618f,
    float delay = 0.0f,
    float zOrder = 0.0f,
    string fontName="vag",
    float FontSize=18.0f,
    ofVec2f Scale = ofVec2f(1.0f,1.0f),
    ofColor CrFill = ofColor::white,
    float edgeSize = 1.0f,
    ofColor CrEdge = ofColor::black
    )
  {
    {  
      ofPtr<TextNode> TN= 
        TextNode::create(
        ofToString(msg),
        &ofxAssets::font(fontName,FontSize),
        pos,
        CrFill,
        edgeSize,
        CrEdge);
      TN->setScale(Scale);
      ofPtr<ofxNodeCtrlLua> NCL;
      NCL.reset(new ofxNodeCtrlLua(
        LuaFcnName,1.0f,LuaScriptPath));
      INFORMER.pushInfo(TN,duration,delay,zOrder,1.0f,NCL);      
      return TN;
    }
  }

  template<typename T>
  vector<ofPtr<ofNode> > pushInfoWithBalloon(
    T msg,
    ofVec2f pos, 
    ofVec2f balloonScale = ofVec2f(1.4f,1.8f),
    string balloonScript = "Lua\\balloonScript0.lua",
    float duration = 0.618f,
    float delay = 0.0f,
    float zOrder = 0.0f,    
    ofColor balloonFillColor = ofColor::white,
    float balloonEdgeSize = 2.0f,
    ofColor balloonEdgeColor = ofColor::black,    
    string fontName="vag",    
    float FontSize=18.0f,
    ofVec2f Scale = ofVec2f(1.0f,1.0f),
    ofColor CrFill = ofColor::black,
    float edgeSize = 0.0f,
    ofColor CrEdge = ofColor::white
    )
  {
    {  
      ofPtr<TextNode> TN= 
        TextNode::create(
        ofToString(msg),
        &ofxAssets::font(fontName,FontSize),
        pos,
        CrFill,
        edgeSize,
        CrEdge);
      TN->setScale(Scale);      
      ofPtr<BalloonNode> BN = BalloonNode::create(
        TN,
        balloonFillColor,
        balloonEdgeSize,
        balloonEdgeColor,
        balloonScale);
      BN->loadLuaScript(balloonScript);
      INFORMER.pushInfo(BN,duration,delay,zOrder);
      INFORMER.pushInfo(TN,duration,delay,zOrder);  
      vector<ofPtr<ofNode> > Ns;
      Ns.push_back(BN);
      Ns.push_back(TN);
      return Ns;
    }
  }

  ofPtr<ofNode> pushResizingCircle(
    ofVec2f pos,
    float duration = 1.0f,
    float delay = 0.0f,
    float zOrder = 0.0f,
    float spd = 1.0f,
    ofVec2f Scale = ofVec2f(1,1),    
    float radius0 = 50.0f, 
    float radius1 = 3.0f,
    float lineWidth0 = 1.0f,
    float lineWidth1= 5.0f,
    ofColor cr0 = ofColor(0,255,0,0),
    ofColor cr1 = ofColor(0,255,0,255),
    ResizingCircleNode::WrapMode wmode =  
      ResizingCircleNode::WrapMode::MIRRORED_REPEAT
    );
  
}

