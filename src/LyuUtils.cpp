#include "LyuUtils.h"
#include <algorithm>

namespace Lyu
{
  void Lyu::drawTxtByFontFillRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect,
    float EdgeWidth)
  {        
    // 获得Txt以(0,0)以起点显示所处的包围盒矩形R0
    ofRectangle R0 = 
      pFont->getStringBoundingBox(Txt,0,0);
    ofVec2f Ctr(R0.getCenter()); // 矩形中心

    // 将Txt以(0,0)为中心显示所需的基准点Base
    ofVec2f Base(-Ctr.x,-Ctr.y);    

    // 获得从R0变换到矩形Rect的变换参数:
    // 平移量 tx,ty;
    float tx,ty;
    tx = Rect.getCenter().x;
    ty = Rect.getCenter().y;     
    // 缩放尺度sx,sy 
    float sx,sy;
    sx = Rect.getWidth()/R0.getWidth();
    sy = Rect.getHeight()/R0.getHeight();
    
    ofMatrix4x4 Mat;
    // 计算变换矩阵
    Mat.preMultTranslate(ofVec3f(tx,ty,0));
    Mat.preMultScale(ofVec3f(sx,sy,1.0f)); 
    // 用矩阵Mat进行变换：从R0变换到Rect
    ofMultMatrix(Mat);

    //从基准点Base用pFont绘制文本Txt
    if(EdgeWidth<=0.0f)
    {
      pFont->drawString(Txt,Base.x,Base.y);       
    }
    else
    {     
      string TxtR = revertTextLines(Txt);      
      size_t n = std::count(TxtR.begin(), TxtR.end(), '\n');
      float dy = (n-1)*pFont->getLineHeight();
      ofVec2f Trans = Base;
      ofTranslate(Trans);
      vector<ofTTFCharacter> Chs = 
        pFont->getStringAsPoints(TxtR,true);  
      ofTranslate(0,dy);
      for(auto &c:Chs)      {
        
        for(auto &pl:c.getOutline())
        {         
          pl.draw();          
        }
      }
      ofTranslate(0,-dy);
      ofTranslate(-Trans);
    }    

    // 进行逆变换：从Rect变换到R0
    ofMatrix4x4 MatI; // Mat的逆矩阵：实现Mat的反向变换
    MatI = Mat.getInverse();
    ofMultMatrix(MatI); // 实现逆变换
  }

  void drawTxtByFontFillRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height,
    float EdgeWidth)
  {
    ofRectangle R; // 矩形类
    // 将矩形设为中心在Pos,长宽为width和height的矩形
    R.setFromCenter(Pos,width,height);     
    drawTxtByFontFillRect(Txt,pFont,R,EdgeWidth);// 嵌套调用
  }


  void drawTxtByFontAt( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    ofVec2f Scale,
    float EdgeWidth /*= 0.0f*/ )
  {
    ofRectangle R = pFont->getStringBoundingBox(Txt,0,0);
    ofRectangle RD;
    RD.setFromCenter(Pos,R.getWidth(),R.getHeight());
    RD.scaleFromCenter(Scale);    
    //cout << "RD:"<< RD << endl;
    drawTxtByFontFillRect(Txt,pFont,RD,EdgeWidth);    
  }
  
  void drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofRectangle Rect, 
    float EdgeWidth /*= 0.0f*/ )
  {
    ofRectangle R = pFont->getStringBoundingBox(Txt,0,0);
    R.setFromCenter(
      Rect.getCenter(),R.getWidth(),R.getHeight());
    float ratio0 = R.getWidth()/R.getHeight();
    float ratio1 = Rect.getWidth()/Rect.getHeight();
    if(ratio0>ratio1)
    {
      float ratio = Rect.getWidth()/R.getWidth();
      R.scaleFromCenter(ratio);
    }
    else
    {
      float ratio = Rect.getHeight()/R.getHeight();
      R.scaleFromCenter(ratio);
    }    
   
    drawTxtByFontFillRect(Txt,pFont,R,EdgeWidth);    
  }

  void drawTxtByFontInRect( 
    string Txt, 
    ofTrueTypeFont* pFont, 
    ofVec2f Pos, 
    float width, 
    float height, 
    float EdgeWidth /*= 0.0f*/ )
  {
    ofRectangle R;
    R.setFromCenter(Pos,width,height);
    drawTxtByFontInRect(Txt,pFont,R,EdgeWidth);
  }

  ofMesh genRectMesh( float x, float y, float wd, float ht )
  {
    ofMesh M;
    M.clear();
    M.setMode(OF_PRIMITIVE_TRIANGLES);

    M.addVertex(ofVec2f(x,y));
    M.addVertex(ofVec2f(x+wd,y));
    M.addVertex(ofVec2f(x,y+ht));
    M.addVertex(ofVec2f(x+wd,y+ht));

    M.addTexCoord(ofVec2f(0,0));
    M.addTexCoord(ofVec2f(1,0));
    M.addTexCoord(ofVec2f(0,1));
    M.addTexCoord(ofVec2f(1,1));

    ofIndexType ids[6] = {0,1,3,0,2,3};
    M.addIndices(ids,6);

    return M;
  }

  float getMeshArea( ofMesh* msh )
  {
    vector<ofMeshFace> Fs = msh->getUniqueFaces();
    float Area(0);
    for(const auto& item:Fs) // C++ 11 feature
    {
      ofVec3f P0 = item.getVertex(0);
      ofVec3f P1 = item.getVertex(1);
      ofVec3f P2 = item.getVertex(2);

      ofVec3f P01 = P1-P0;
      ofVec3f P02 = P2-P0;

      ofVec3f C = P01.crossed(P02);
      float A = 0.5*C.length();
      Area += A;   
    }
    return Area;
  }

  float getMeshRadius( ofMesh* msh )
  {
    ofVec3f C = msh->getCentroid();
    int NumVts = msh->getNumVertices();
    float Radius(0);
    for(int i=0;i<NumVts;i++)
    {
      ofVec3f Vt = msh->getVertex(i);
      float Dist = Vt.distance(C);
      Radius = Dist>Radius?Dist:Radius;
    }
    return Radius;
  }

  bool isIdentity( ofMatrix4x4& A, ofMatrix4x4& B )
  {
    for(int i=0;i<16;i++)
    {
      if(*(A.getPtr()+i)!=*(B.getPtr()+i))
      {
        return false;
      }
    }
    return true;
  }

  ofMesh genLineMesh( ofPoint P0, ofPoint P1 )
  {
    ofMesh M;
    M.setMode(OF_PRIMITIVE_LINES);
    M.addVertex(P0);
    M.addVertex(P1);
    return M;
  }

  ofMesh genCircleMesh( 
    ofPoint Center, 
    float Radius, 
    int Resolution/*=36*/)
  {
    ofMesh Mesh;    
    Mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    Mesh.addVertex(Center);
    Mesh.addTexCoord(ofVec2f(0.5f,0.5f));

    float radStep = 2.0f*PI/Resolution;    
    for(int i=0;i<Resolution+1;i++)
    {
      float theta = i*radStep;
      float x = cos(theta);
      float y = sin(theta);
      Mesh.addVertex(Center+Radius*ofVec3f(x,y,0));

      ofVec2f TC(x,y);
      TC = 0.5f*(TC+ofVec2f(1,1));
      Mesh.addTexCoord(TC);

      int Num = Mesh.getNumVertices();
      if(Num>2)
      {
        Mesh.addIndex(0);
        Mesh.addIndex(Num-2);
        Mesh.addIndex(Num-1);
      }
    }
    return Mesh;
  }

  ofMesh genTriangleMesh( ofPoint P0, ofPoint P1, ofPoint P2 )
  {
    ofMesh Mesh;    
    Mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    Mesh.addVertex(P0);
    Mesh.addVertex(P1);
    Mesh.addVertex(P2);

    Mesh.addIndex(0);
    Mesh.addIndex(1);
    Mesh.addIndex(2);

    Mesh.addTexCoord(ofVec2f(0,0));
    Mesh.addTexCoord(ofVec2f(1,0));
    Mesh.addTexCoord(ofVec2f(0,1));

    return Mesh;
  }

  ofMesh genTriangleMesh( 
    ofPoint Center, float Radius, float RotDeg)
  {    
    ofVec2f Vec = ofVec2f(1,0)*Radius;    
    ofPoint P1 = Center + Vec.rotated(RotDeg);
    ofPoint P2 = Center + Vec.rotated(120+RotDeg);
    ofPoint P3 = Center + Vec.rotated(240+RotDeg); 
    return genTriangleMesh(P1,P2,P3);
  }

  double sampleNormal()
  {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
  }

  std::string revertTextLines( string Txt )
  {
    string TxtR;
    stringstream ss;
    ss << Txt << endl;
    ofBuffer B;
    B.set(ss);      
    vector<string> TextLines;
    while(!B.isLastLine())
    {
      TextLines.push_back(B.getNextLine());
    }
    
    stringstream ss3;
    vector<string>::reverse_iterator ritl;
    if(TextLines.size()==1)
    {
      ss3 << TextLines[0] << endl;
    }
    else
    {
      for(ritl=TextLines.rbegin()+1;ritl<TextLines.rend();ritl++)
      {        
        ss3 << *ritl << endl;
      } 
    }       
    return ss3.str();
  }

  float getWindowSize()
  {
    return sqrt(ofGetWidth()*ofGetHeight());
  }

}

