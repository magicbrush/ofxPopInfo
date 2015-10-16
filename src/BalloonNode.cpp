#include "BalloonNode.h"
#include "ofxLua.h"
#define ToString(x) #x

namespace Lyu
{
  ofPtr<ofxLua> BalloonNode::L;

  std::string BalloonNode::ExitScript = ToString(    
    loadstring(Pref .. "=nil")());

  string 
    ExitScript, BalloonNode::LuaRectParamsInitScript = 
    ToString(
      PL = nil
      PL = of.Polyline()
      PL:clear()
      loadstring("x =" .. Pref .. "blx")()	
      loadstring("y =" .. Pref .. "bly")()
      PL:addVertex(x,y,0.0)	
      loadstring("x =" .. Pref .. "brx")()	
      loadstring("y =" .. Pref .. "bry")()
      PL:addVertex(x,y,0.0)	
      loadstring("x =" .. Pref .. "trx")()	
      loadstring("y =" .. Pref .. "try")()
      PL:addVertex(x,y,0.0)
      loadstring("x =" .. Pref .. "tlx")()	
      loadstring("y =" .. Pref .. "tly")()
      PL:addVertex(x,y,0.0)
      PL:close()     
      
      CrEdge = nil
      CrFill = nil
      CrEdge = of.Color()
      CrFill = of.Color();
      loadstring("CrEdge.r =" .. Pref .. "cer")()	
      loadstring("CrEdge.g =" .. Pref .. "ceg")()
      loadstring("CrEdge.b =" .. Pref .. "ceb")()	
      loadstring("CrEdge.a =" .. Pref .. "cea")()
      loadstring("CrFill.r =" .. Pref .. "cfr")()	
      loadstring("CrFill.g =" .. Pref .. "cfg")()
      loadstring("CrFill.b =" .. Pref .. "cfb")()	
      loadstring("CrFill.a =" .. Pref .. "cfa")()
      loadstring("EdgeWidth = ".. Pref .. "EdgeWidth")()      
    );

  BalloonNode::BalloonNode( 
    float width, 
    float height,
    float edgeWidth/*=1.0f*/, 
    ofColor edgeColor/*=ofColor::black*/, 
    ofColor fillColor/*=ofColor::white*/ ):
  R(-width/2,-height/2,width,height),
  EdgeWidth(edgeWidth),
  CrEdge(edgeColor),
  CrFill(fillColor)
  {
    float Vt[8] = {
      R.getBottomLeft().x,
      R.getBottomLeft().y,
      R.getBottomRight().x,
      R.getBottomRight().y,
      R.getTopLeft().x,
      R.getTopLeft().y,
      R.getTopRight().x,
      R.getTopRight().y};
    R_vertices = vector<float>(Vt,Vt+8);
  }

  BalloonNode::~BalloonNode()
  {
    if(L.use_count()>0)
      L->doString(ExitScript);    
  }

  void BalloonNode::customDraw()
  {
    if(L.use_count()>0)
    {
      initLua();
      L->scriptFcn(DrawFcn);
    }
    else
    {      
      ofPushStyle();
      ofFill();
      ofSetColor(CrFill);
      ofRect(R);
      ofNoFill();
      ofSetColor(CrEdge);
      ofSetLineWidth(EdgeWidth);
      ofRect(R);
      ofPopStyle();      
    }

   
  }

  void BalloonNode::loadLuaScript( 
    string luaPath,    
    string drawFcn /*= "draw" */)
  {
    LuaPath = luaPath;
    initLua();
    
    DrawFcn = drawFcn;
    unsigned long T = ofGetElapsedTimeMillis();
    Pref = "P" + ofToString(this) + ofToString(T);     
  }    
  
  void BalloonNode::initLua()
  {
    if(L.use_count()==0)
    {
      L.reset(new ofxLua);
    }
    if(!L->isInited())
    {
      L->init(false,true,true);            
    }
    L->doScript(LuaPath);
    resetLuaBalloonParams();
  }  

  void BalloonNode::resetLuaBalloonParams()
  {
    L->setString("Pref",Pref);
    L->setFloat(Pref+"blx",R_vertices[0]);
    L->setFloat(Pref+"bly",R_vertices[1]);
    L->setFloat(Pref+"brx",R_vertices[2]);
    L->setFloat(Pref+"bry",R_vertices[3]);
    L->setFloat(Pref+"tlx",R_vertices[4]);
    L->setFloat(Pref+"tly",R_vertices[5]);
    L->setFloat(Pref+"trx",R_vertices[6]);
    L->setFloat(Pref+"try",R_vertices[7]);
    L->setFloat(Pref+"cer",CrEdge.r);
    L->setFloat(Pref+"ceg",CrEdge.g);
    L->setFloat(Pref+"ceb",CrEdge.b);
    L->setFloat(Pref+"cea",CrEdge.a);
    L->setFloat(Pref+"cfr",CrFill.r);
    L->setFloat(Pref+"cfg",CrFill.g);
    L->setFloat(Pref+"cfb",CrFill.b);
    L->setFloat(Pref+"cfa",CrFill.a);
    L->setFloat(Pref+"EdgeWidth",EdgeWidth);
    L->doString(LuaRectParamsInitScript);
  }

  ofPtr<BalloonNode> BalloonNode::create( 
    ofPtr<TextNode> TxtN, 
    ofColor crFill /*= ofColor::white*/, 
    float edgeWidth /*= 2.0f*/, 
    ofColor crEdge /*= ofColor::black*/, 
    ofVec2f Scal /*= ofVec2f(1.2,1.2)*/ )
  {   
    ofRectangle RTxt = TxtN->getTextRect();
    ofPtr<BalloonNode> BN;
    BN.reset(new BalloonNode(
      RTxt.getWidth(),
      RTxt.getHeight(),
      edgeWidth,
      crEdge,     
      crFill));
    ofMatrix4x4 Mat = TxtN->getGlobalTransformMatrix();
    Mat.preMultScale(Scal);
    BN->setTransformMatrix(Mat);    
    return BN;
  }
}