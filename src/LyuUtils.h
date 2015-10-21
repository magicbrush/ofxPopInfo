#pragma  once
#ifndef $$LYUUTILS_H$$
#define $$LYUUTILS_H$$

#include "ofMain.h"

#include "math.h" // for RAND, and rand

namespace Lyu
{
  // �ھ���Rect��������pFont����ʾ�ı�Txt
  void drawTxtByFontFillRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect,
    float EdgeWidth = 0.0f);
  // ��PosΪ���ĵĿ��Ϊwidth���߶�Ϊheight�ľ��η�Χ�ڣ�
  // ������pFont��ʾ�ı�Txt
  void drawTxtByFontFillRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height,
    float EdgeWidth = 0.0f);
  void drawTxtByFontAt(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    ofVec2f Scale = ofVec2f(1,1),
    float EdgeWidth = 0.0f);
  void drawTxtByFontInRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofRectangle Rect,
    float EdgeWidth = 0.0f);
  void drawTxtByFontInRect(
    string Txt,
    ofTrueTypeFont* pFont, 
    ofVec2f Pos,
    float width,
    float height,
    float EdgeWidth = 0.0f);

  // Text
  string revertTextLines( string Txt );

  // mesh 
  ofMesh genRectMesh(float x, float y, float wd, float ht);
  ofMesh genLineMesh(ofPoint P0, ofPoint P1);
  ofMesh genCircleMesh(
    ofPoint Center, float Radius, int Resolution=36);
  ofMesh genTriangleMesh(ofPoint P0, ofPoint P1, ofPoint P2);
  ofMesh genTriangleMesh(
    ofPoint Center, float Radius, float RotDeg=float(0));
  float getMeshArea(ofMesh* msh);  
  float getMeshRadius(ofMesh* msh);  
  
  // matrix
  bool isIdentity(ofMatrix4x4& A, ofMatrix4x4& B);

  // math
  // get rand num by normal distribution
  double sampleNormal(); 

  // size
  float getWindowSize();

}

#endif