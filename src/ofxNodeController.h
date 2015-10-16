#pragma once

#include "ofMain.h"

namespace Lyu
{
  class ofxNodeController
  {
  public:
    virtual void update(ofNode* pn)=0;
  };
}