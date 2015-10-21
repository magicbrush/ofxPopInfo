#pragma once

#include "ofMain.h"

namespace Lyu
{
  class ofxNodeCtrlLua;
}

class CircleNode:
  public ofNode
{
public:
  CircleNode(ofVec2f Vel = ofVec2f(ofRandom(-3,3),ofRandom(-3,3)));  
  virtual void customDraw() override;
  ofVec2f V;

};

class ofApp : public ofBaseApp{

	public:
		void setup();
    void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void resetParticlesProps();

    vector<ofPtr<ofNode> > Particles;
    ofPtr<ofNode> pN;		
    ofPtr<Lyu::ofxNodeCtrlLua> NCtrlLua;
    int idLuaFcn;
};
