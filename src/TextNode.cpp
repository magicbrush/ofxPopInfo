#include "TextNode.h"
#include "LyuUtils.h"

namespace Lyu
{
  ofPtr<TextNode> TextNode::create(
    string msg, 
    ofTrueTypeFont* font/*=nullptr*/, 
    ofVec3f Pos/*=ofVec2f(ofGetWidth()/2,ofGetHeight()/2)*/, 
    ofColor crFill /*= ofColor::white*/, 
    float edgeWidth /*= 0.0f*/, 
    ofColor crEdge /*= ofColor::black*/, 
    ofVec2f Scal /*= ofVec2f(1,1)*/, 
    ofQuaternion Orin /*= ofQuaternion()*/ )
  {
    ofPtr<TextNode> TN;
    TN.reset(new TextNode(
      msg,font,crFill,edgeWidth,crEdge));
    TN->setPosition(Pos);
    TN->setScale(Scal);
    TN->setOrientation(Orin);
    return TN;
  }
  
  TextNode::TextNode(
    string msg, 
    ofTrueTypeFont* font/*=nullptr*/, 
    ofColor crFill /*= ofColor::white*/, 
    float edgeWidth /*=1.0f*/, 
    ofColor crEdge /*= ofColor(0,0,0,0)*/ ):
    Msg(msg),
    f(font),
    CrFill(crFill),
    EdgeWidth(edgeWidth),
    CrEdge(crEdge)
  {

  }

  void TextNode::customDraw()
  {
    if(Msg=="")return;

    ofPushStyle();
    if(f==nullptr)
    {
      ofDrawBitmapStringHighlight(
        Msg,0,0,CrEdge,CrFill);      
    }
    else
    {      
      ofSetColor(CrFill);
      Lyu::drawTxtByFontAt(
        Msg,f,ofVec2f(0,0),ofVec2f(1,1));
      if(EdgeWidth>0.0)
      {
        ofSetColor(CrEdge);
        Lyu::drawTxtByFontAt(
          Msg,f,ofVec2f(0,0),ofVec2f(1,1),EdgeWidth);
      }            
    }    
    ofPopStyle();
  }

  ofRectangle TextNode::getTextRect()
  {
    ofRectangle R = f->getStringBoundingBox(Msg,0,0);
    R.translate(-R.getCenter());
    return R;
  }


}