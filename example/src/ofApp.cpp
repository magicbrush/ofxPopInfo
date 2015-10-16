#include "ofApp.h"
#include "SingletonTemplate.h"
#include "Informer.h"
#include "ofxLua.h"
#include "ResizingCircleNode.h"
#include "ArcBarNode.h"
#include "TimerNode.h"
#include "ofxAssets.h"
#include "ofxNodeCtrlLua.h"

using namespace Lyu;

//--------------------------------------------------------------
void ofApp::setup(){
  pN.reset(new ofNode());
  pN->setPosition(ofVec2f(600,600));
  NCtrlLua.reset(new Lyu::ofxNodeCtrlLua());
  idLuaFcn = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
  INFORMER.update();

  NCtrlLua->update(pN.get());
}

//--------------------------------------------------------------
void ofApp::draw(){
  INFORMER.draw();

  stringstream ss;
  ss << "F1: rectangle balloon: Lua\\balloonRectangle.lua" << endl;
  ss << "F2: noise balloon: Lua\\balloonNoise.lua" << endl;
  ss << "F3: bubbles balloon: Lua\\balloonBubbles.lua" << endl;
  ss << "F4: test balloon: Lua\\balloonOval.lua" << endl;
  ss << "F5: test balloon: Lua\\balloonscript0.lua" << endl;  
  ss << "F6: Timer" << endl;
  ss << "F7: Counter" << endl;
  ss << "F8: Test Lua Control" << endl;
  ss<< " r: reload Lua scripts " << endl;
  ofPushStyle();
  ofSetColor(0);
  ofDrawBitmapString(ss.str(),5,15);
  ofPopStyle();

  pN->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  string S = ofToString(key)+" is pressed!";
  Lyu::pushInfo(
    S,
    ofVec2f(ofGetWidth()/2,ofGetHeight()/2),
    1.5f,
    0.1f,
    0.0f);

  if(key==OF_KEY_F1)
  {
    stringstream ss;
    ss << " test pushInfoWithBalloon " << endl;
    ss << " The weather today is perfect!" << endl;
    Lyu::pushInfoWithBalloon(
      ss.str(),
      ofVec2f(ofGetWidth()/2,200),
      ofVec2f(1.5f,2.2f),
      "Lua\\balloonRectangle.lua",
      2.5f);
  }
  if(key==OF_KEY_F2)
  {
    stringstream ss;    
    ss << " ORZ!!!!!!!!" << endl;
    ss << " OH! MY GOD!" << endl;
    ss << " ???????????" << endl;
    ss << "    Er?     " << endl;
    Lyu::pushInfoWithBalloon(
      ss.str(),
      ofVec2f(ofGetWidth()/1.5,400),
      ofVec2f(1.5f,2.2f),
      "Lua\\balloonNoise.lua",
      2.5f);
  }
  if(key==OF_KEY_F3)
  {
    stringstream ss;   
    ss << " This is a game!" << endl;
    ss << " Stone" << endl;
    ss << "           Brrrrrr!" << endl;    
    Lyu::pushInfoWithBalloon(
      ss.str(),
      ofVec2f(ofGetWidth()/3,600),
      ofVec2f(1.6f,2.5f),
      "Lua\\balloonBubbles.lua",
      2.5f);
  }
  if(key==OF_KEY_F4)
  {    
    stringstream ss;
    ss << "Good!!" << endl;
    ss << "Bad!!!" << endl;   
    Lyu::pushInfoWithBalloon(
      ss.str(),
      ofVec2f(600,600),
      ofVec2f(1.4f,2.2f),
      "Lua\\balloonOval.lua",
      2.5f);
  }
  if(key==OF_KEY_F5)
  {    
    stringstream ss;
    ss << " This is a game!" << endl;
    ss << " Stone" << endl;
    ss << "           Brrrrrr!" << endl;    
    Lyu::pushInfoWithBalloon(
      ss.str(),
      ofVec2f(300,300),
      ofVec2f(1.6f,2.5f),
      "Lua\\balloonScript0.lua",
      2.5f);
  }  
  if(key==OF_KEY_F6)
  {
    float duration = ofRandom(5,15);
    ofVec3f Pos(200,200,0);
    ofPtr<Lyu::TimerNode> TN;
    TN = Lyu::TimerNode::createTimer(
      Pos,
      ofVec3f(1,1,1),
      &ofxAssets::font("vag",24),
      duration,
      0.0f);
    INFORMER.pushInfo(TN,duration,0,2.0f);
    ofPtr<Lyu::ArcBarNode> AN;
    AN.reset(new Lyu::ArcBarNode(duration,60,80,1.0));
    AN->setPosition(Pos);
    INFORMER.pushInfo(AN,duration,0,2.1f);
  }
  if(key==OF_KEY_F7)
  {
    float duration = ofRandom(5,15);
    ofVec3f Pos(300,200,0);
    ofPtr<Lyu::TimerNode> TN;
    TN = Lyu::TimerNode::createCounter(
      100,0,
      Pos,
      ofVec3f(1,1,1),
      &ofxAssets::font("vag",24),
      duration,
      0.0f);
    INFORMER.pushInfo(TN,duration,0,2.0f);
    ofPtr<Lyu::ArcBarNode> AN;
    AN.reset(new Lyu::ArcBarNode(duration,50,60,0.0));
    AN->setPosition(Pos);
    INFORMER.pushInfo(AN,duration,0,2.1f);
  }
  if(key==OF_KEY_F8)
  {
    string LuaFcnName[5] = {
      "zoomInOut","ascend","rolling","trembling","shaking"};
    string LuaFN = LuaFcnName[idLuaFcn];
    stringstream ss;
    ss << " ---------------PEOPLE--" << endl;
    ss << " Test Lua Script Control" << endl;
    ss << "    "<< LuaFN << "    " << endl;
    ss << " -----ABCDEFGHIJ--------" << endl;
    Lyu::pushInfoWithLuaCtrl(
      ss.str(),
      ofVec2f(idLuaFcn*100+100,300),
      "Lua\\ofxNodeCtrlLua.lua",
      LuaFN,
      5.0f,
      0.5f);
    idLuaFcn++;
    idLuaFcn = idLuaFcn%5;
  }
  else if(key=='r')
  {
    ofxLua::clearAllofxLuas(); 
    pN->setPosition(ofVec2f(600,600));
  } 

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  if(button==0)
  {
    Lyu::pushResizingCircle(ofVec2f(x,y),1.0f,0.0f,1.0f,1.0f);
  }
  else if(button==2)
  {
    
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if(button==0)
  {
    Lyu::pushInfoWithBalloon(ofVec2f(x,y),ofVec2f(x,y));
  }
  else if(button==2)
  {
   
  }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  if(button==0)
  {
    
  }
  else if(button==2)
  {    
    
  }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
