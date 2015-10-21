#include "ofApp.h"
#include "ofxPopInfo.h"

using namespace Lyu;

//--------------------------------------------------------------
void ofApp::setup(){
  pN.reset(new ofNode());
  pN->setPosition(ofVec2f(600,600));
  NCtrlLua.reset(new Lyu::ofxNodeCtrlLua());
  idLuaFcn = 0;

  for(int i=0;i<20;i++)
  {
    ofPtr<CircleNode> P;
    P.reset(new CircleNode);   
    Particles.push_back(P);
  }

  resetParticlesProps();

}

//--------------------------------------------------------------
void ofApp::update(){
  INFORMER.update(); 

  NCtrlLua->update(pN.get());    
}

//--------------------------------------------------------------
void ofApp::draw(){
  pN->draw();
  for(auto &P:Particles)
    P->draw();

  INFORMER.draw();
  stringstream ss;
  ss << "F1: rectangle balloon: Lua\\balloonRectangle.lua" << endl;
  ss << "F2: noise balloon: Lua\\balloonNoise.lua" << endl;
  ss << "F3: bubbles balloon: Lua\\balloonBubbles.lua" << endl;
  ss << "F4: test balloon: Lua\\balloonOval.lua" << endl;
  ss << "F5: test balloon: Lua\\balloonscript0.lua" << endl;  
  ss << "F6: Timer" << endl;
  ss << "F7: Counter" << endl;
  ss << "F8: Test Lua Node Control" << endl;
  ss << "F9: Info Balloon with Lua Node Control" << endl;
  ss << "F10: Test Lua Node Control multiple ofNodes" << endl;
  ss<< " r: reload Lua scripts, reset particles" << endl;
  ofPushStyle();
  ofSetColor(0);
  ofDrawBitmapString(ss.str(),5,15);

  string fps = ofToString(ofGetFrameRate(),5);
  ofDrawBitmapString("Fps:" + fps,5,ofGetHeight()-15);
  ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  string S = ofToString(key)+" is pressed!";
  INFORMER.pushInfoAt(
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
    INFORMER.pushInfoWithBalloon(
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
    INFORMER.pushInfoWithBalloon(
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
    INFORMER.pushInfoWithBalloon(
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
    INFORMER.pushInfoWithBalloon(
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
    INFORMER.pushInfoWithBalloon(
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
      "zoomInOut","ascend","rolling","trembling","shakingAround"};
    string LuaFN = LuaFcnName[idLuaFcn];
    stringstream ss;   
    ss << "-----------------------------" << endl;
    ss << " Test Lua Script Control" << endl;
    ss << "     "<< LuaFN << "     " << endl;
    ss << "-----------------------------" << endl;
    ofVec2f Pos(idLuaFcn*100+200,300);
    string Text = ss.str();
    INFORMER.pushInfoWithLuaCtrl(
      Text,
      Pos,
      "Lua\\ofxNodeCtrlLua.lua",
      LuaFN,
      5.0f,0.1f);
    idLuaFcn++;
    idLuaFcn = idLuaFcn%5;    
  }
  if(key==OF_KEY_F9)
  {    
    stringstream ss;
    string TxtLuaFcn = "zoomInOut";
    string BalloonLuaFcn = "trembling";
    ss << " Balloon Balloon!" << endl;
    ss << TxtLuaFcn << endl;
    ss << BalloonLuaFcn << endl;    
    INFORMER.pushInfoBalloonWithNodeCtrl(
      ss.str(),
      ofVec2f(300,600),
      TxtLuaFcn,
      ofVec2f(1.1f,1.4f),
      BalloonLuaFcn,
      "Lua\\balloonScript0.lua",
      2.5f);
  }  
  if(key==OF_KEY_F10)
  {
    string LuaFcnName[5] = {
      "zoomInOut",
      "ascend",
      "rolling",
      "trembling",
      "shakingAround"};
    string LuaFN = LuaFcnName[idLuaFcn];
    stringstream ss;     
    INFORMER.pushNodeCtrlLuas(
      Particles,
      LuaFN,
      "Lua\\ofxNodeCtrlLua.lua",
      1.0f,
      0.0f,
      1.0f);
    idLuaFcn++;
    idLuaFcn = idLuaFcn%5;
    INFORMER.pushInfoAt(
      LuaFN,ofVec2f(ofGetWidth()/2,ofGetHeight()/3),
      1.5f,0.0f,1.0f);
  }
  else if(key=='r')
  {
    ofxLua::clearAllofxLuas(); 
    pN->setPosition(ofVec2f(600,600));
    resetParticlesProps();
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
    INFORMER.pushResizingCircle(ofVec2f(x,y),1.0f,0.0f,1.0f,1.0f);
  }
  else if(button==2)
  {
    
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  if(button==0)
  {
    INFORMER.pushInfoWithBalloon(ofVec2f(x,y),ofVec2f(x,y));
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

void ofApp::resetParticlesProps()
{
  for(auto &P:Particles)
  {
    P->setPosition(
      ofVec2f(
      ofRandom(0,ofGetWidth()),
      ofRandom(0,ofGetHeight())));
    P->setScale(ofRandom(0.3,2),ofRandom(0.3,2),1);     
  }
}

void CircleNode::customDraw()
{
  ofCircle(ofPoint(0,0),20.0f);
  ofDrawAxis(20);

  move(V);

  ofVec3f P = getPosition();
  P.x = ofWrap(P.x,0,ofGetWidth());
  P.y = ofWrap(P.y,0,ofGetHeight());
  setPosition(P);
}

CircleNode::CircleNode( 
  ofVec2f Vel /*= ofVec2f(ofRandom(-3,3),ofRandom(-3,3))*/ ):
  V(Vel)
{}
