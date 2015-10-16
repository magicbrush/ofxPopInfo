#include "Informer.h"
#include "ofxNodeController.h"

namespace Lyu
{
  Informer::Informer()
  {
    timeLast = ofGetElapsedTimef();
  }

  Informer::~Informer()
  {}
  
  void Informer::update()
  {
    float timeNow = ofGetElapsedTimef();
    float dt = timeNow - timeLast;
    updateINodes(dt);
    updateNodeCtrls(dt);
    timeLast = timeNow;
  }

  void Informer::draw( float x, float y )
  {
    float wd = ofGetWidth();
    float ht = ofGetHeight();
    draw(x,y,wd,ht);
  }

  void Informer::draw( 
    float x, float y, float w, float h )
  {
    ofPushView();
    ofViewport(x,y,w,h);
    for(auto &info:I)
    {
      info.second.iNode->draw();
    }
    ofPopView();
  }

  float Informer::getHeight()
  {
    return ofGetWidth();
  }

  float Informer::getWidth()
  {
    return ofGetHeight();
  }

  void Informer::pushInfo( 
    ofPtr<ofNode> Info, 
    float duration /*= 1.0f*/, 
    float delay /*= 0.0f*/, 
    float zOrder /*= 0.0f*/, 
    float speed /*= 1.0f*/,
    ofPtr<ofxNodeController> nCtrl)
  {
    speed = ofClamp(speed,0.01,100.0f);
    while(I.find(zOrder)!=I.end())
    {
      float zo2 = zOrder + 0.000001f;
      if(zo2==zOrder)
      {
        zOrder = zOrder + abs(zOrder*0.00001f)+0.00001f;
      }
      else
      {
        zOrder = zo2;
      }      
    }
    InfoStruct MSG;
    MSG.iNode = Info;
    MSG.duration = duration;
    MSG.delay = delay;
    MSG.speed = speed;
    I[zOrder] = MSG;

    pushNodeCtrl(nCtrl,MSG.iNode,duration,delay,speed);    
  }

  void Informer::clear()
  {
    I.clear();
  }

  void Informer::removeInfo( ofPtr<ofNode> Info )
  {
    map<float,InfoStruct>::iterator it;
    for(it=I.begin();it!=I.end();it++)
    {
      if(it->second.iNode==Info)break;
    }
    I.erase(it);
  }

  void Informer::removeInfo( float zOrder )
  {
    I.erase(I.find(zOrder));
  }

  void Informer::changeDuration( 
    ofPtr<ofNode> Info, float duration )
  {
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)obj.second.duration = duration;      
    }
  }

  void Informer::changeSpeed( 
    ofPtr<ofNode> Info, float speed )
  {
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)obj.second.speed = speed;      
    }
  }

  void Informer::changeZOrder( 
    ofPtr<ofNode> Info, float zOrder )
  {
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)
      {
        I[zOrder] = obj.second;
        I.erase(obj.first);
      }
    }
  }

  void Informer::changeDelay( 
    ofPtr<ofNode> Info, float delay )
  {
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)obj.second.delay = delay;      
    }
  }

  void Informer::changeInfo( 
    ofPtr<ofNode> Info, 
    float duration, 
    float delay, 
    float zOrder, 
    float speed )
  {
    changeZOrder(Info,zOrder);
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)
      {
        obj.second.duration = duration;
        obj.second.delay = delay;
        obj.second.speed = speed;
      }
    }
  }

  Informer::InfoStruct Informer::getInfo( ofPtr<ofNode> Info )
  {
    for(auto& obj:I)
    {
      if(obj.second.iNode==Info)return obj.second;      
    }
    
    Informer::InfoStruct S;
    return S;
  }

  void Informer::pushNodeCtrl( 
    ofPtr<ofxNodeController> nCtrl,
    ofPtr<ofNode> nTgt,
    float duration /*= 1.0f*/, 
    float delay /*= 0.0f*/, 
    float speed /*= 1.0f*/ )
  {
    if(nCtrl.use_count()==0)
      return;
    NodeCtrlStruct NCS = {nCtrl,nTgt,delay,duration,speed};    
    C.push_back(NCS);
  }

  void Informer::updateINodes( float dt )
  {
    map<float,InfoStruct>::iterator it;
    for(it=I.begin();it!=I.end();it++)
    {
      if(it->second.duration<=0.0f)
      {
        map<float,InfoStruct>::iterator it2 = it;        
        I.erase(it2);
        break;
      }
    }

    for(auto &info:I)
    {
      InfoStruct& M = info.second;      
      if(M.delay>0)
      {
        M.delay -= dt;
      }
      else
      {
        float Dt = dt*M.speed;
        M.duration -= M.speed*M.delay;
        M.delay = 0.0f;
        M.duration -= Dt;        
      }
    }
  }

  void Informer::updateNodeCtrls( float dt )
  {
    vector<NodeCtrlStruct>::iterator it2;
    for(it2=C.begin();it2<C.end();it2++)
    {
      bool bSingleUse = (it2->NTgt.use_count()==1);
      bool bOut = (it2->duration<=0);
      if(bSingleUse||bOut)
      {
        C.erase(it2);
        break;
      }
    }

    for(auto &nc:C)
    {         
      if(nc.delay>0)
      {
        nc.delay -= dt;
      }
      else
      {
        float Dt = dt*nc.speed;
        nc.duration -= nc.speed*nc.delay;
        nc.delay = 0.0f;
        nc.duration -= Dt;
        nc.NCtrl->update(nc.NTgt.get());       
      }
    }
  }

  ofPtr<ofNode> pushResizingCircle( 
    ofVec2f pos, 
    float duration /*= 1.0f*/, 
    float delay /*= 0.0f*/,
    float zOrder /*= 0.0f*/,
    float spd /*= 1.0f*/, 
    ofVec2f Scale /*= ofVec2f(1,1)*/, 
    float radius0 /*= 50.0f*/, 
    float radius1 /*= 3.0f*/, 
    float lineWidth0 /*= 1.0f*/, 
    float lineWidth1/*= 5.0f*/,
    ofColor cr0 /*= ofColor(0,255,0,0)*/, 
    ofColor cr1 /*= ofColor(0,255,0,255)*/, 
    ResizingCircleNode::WrapMode wmode 
    /*= ResizingCircleNode::WrapMode::MIRRORED_REPEAT */ )
  {
    ofPtr<ofNode> pN;
    pN.reset(new ResizingCircleNode(
      duration,
      radius0,radius1,
      lineWidth0,lineWidth1,
      cr0,cr1,
      wmode));
    pN->setPosition(pos);
    pN->setScale(ofVec3f(Scale.x,Scale.y,1.0f));
    INFORMER.pushInfo(pN,duration,delay,zOrder,spd);
    return pN;
  }

}