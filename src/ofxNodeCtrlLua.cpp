#include "ofxNodeCtrlLua.h"
#include "ofxLua.h"

ofPtr<ofxLua> Lyu::ofxNodeCtrlLua::L;
vector<string> Lyu::ofxNodeCtrlLua::ScriptPaths;

Lyu::ofxNodeCtrlLua::ofxNodeCtrlLua( 
  string FcnName,
   float speed,
  string LuaPath/*="Lua\\ofxNodeCtrlLua.lua"*/ ):
LuaFunction(FcnName),
Speed(speed),
bUpdated(false)
{
  if(L.use_count()==0)
  {
    L.reset(new ofxLua());    
  }
  addLuaScript(LuaPath);
}

Lyu::ofxNodeCtrlLua::~ofxNodeCtrlLua()
{}

void Lyu::ofxNodeCtrlLua::update( ofNode* pn )
{
  if(!L->isInited())
  {
    L->init(false,true,true);
    for(auto &LuaPath:ScriptPaths)
      L->doScript(LuaPath);
  }
  
  if(!bUpdated)
  {
    ofVec3f p0 = pn->getPosition();
    ofVec3f s0 = pn->getScale();
    ofVec3f q0 = pn->getOrientationQuat().asVec3();
    Pos0.assign(&p0[0],&p0[0]+3);
    Scl0.assign(&s0[0],&s0[0]+3);
    Quat0.assign(&q0[0],&q0[0]+3);
  }

  bool bTable = L->pushTable("Position");
  if(!bTable)
    return;
  L->popAllTables();
    
  inputLuaState(pn);
  L->scriptFcn(LuaFunction);  
  setNodeFromLuaState(pn);
  bUpdated = true;
}

void Lyu::ofxNodeCtrlLua::resetLuaScript( string LuaPath )
{
  L->clear();  
  ScriptPaths.clear();
  addLuaScript(LuaPath);
}

void Lyu::ofxNodeCtrlLua::addLuaScript( string LuaPath )
{
  ofFile F(LuaPath);
  bool bExist = F.exists();
  if(bExist)
  {    
    if(L.use_count()>0&&L->isInited())
    {
      L->doScript(LuaPath);
    }
    ScriptPaths.push_back(LuaPath);
  }  
}

void Lyu::ofxNodeCtrlLua::inputLuaState( ofNode* pn )
{
  L->setFloat("Speed",Speed);

  ofVec3f P = pn->getPosition();
  vector<float> Pos;
  for(int i=0;i<3;i++)Pos.push_back(P[i]);
  L->setFloatVector("Position",Pos);

  ofVec3f S = pn->getScale();
  vector<float> Scl;
  for(int i=0;i<3;i++)Scl.push_back(S[i]);
  L->setFloatVector("Scale",Scl);

  ofVec4f Q = pn->getOrientationQuat().asVec4();
  vector<float> Quat;
  for(int i=0;i<4;i++)Quat.push_back(Q[i]);
  L->setFloatVector("Orientation",Quat);
    
  L->setFloatVector("Position0",Pos0);
  L->setFloatVector("Scale0",Scl0);
  L->setFloatVector("Orientation0",Quat0);  
}

void Lyu::ofxNodeCtrlLua::setNodeFromLuaState( ofNode* pn )
{
  vector<float> Pos;
  L->getFloatVector("Position",Pos);
  vector<float> Scl;
  L->getFloatVector("Scale",Scl);
  vector<float> Quat;
  L->getFloatVector("Orientation",Quat);

  if(Pos.size()==3)
    pn->setPosition(Pos[0],Pos[1],Pos[2]);
  if(Scl.size()==3)
    pn->setScale(Scl[0],Scl[1],Scl[2]);
  if(Quat.size()==4)
    pn->setOrientation(
    ofQuaternion(Quat[0],Quat[1],Quat[2],Quat[3]));
}
