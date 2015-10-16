#pragma once

#include "ofMain.h"
#include "ofxNodeController.h"

class ofxLua;

namespace Lyu
{
  class ofxNodeCtrlLua:
    public ofxNodeController
  {
  public:
    static void addLuaScript(string LuaPath);
    static void resetLuaScript(string LuaPath = "");

  public:
    ofxNodeCtrlLua(string FcnName = "zoomInOut",
      float speed = 1.0f,
      string LuaPath="Lua\\ofxNodeCtrlLua.lua");
    ~ofxNodeCtrlLua();
    virtual void update( ofNode* pn ) override;
  
  private:
    void inputLuaState( ofNode* pn );
    void setNodeFromLuaState( ofNode* pn );

  private:
    string LuaFunction;
    float Speed;

    static ofPtr<ofxLua> L;  
    static vector<string> ScriptPaths;

  };
}