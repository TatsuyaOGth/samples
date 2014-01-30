#pragma once

#include "BaseScopeManager.h"

class SampleArrayDrawer : public BaseScopeManager
{
public:
    SampleArrayDrawer();
    ~SampleArrayDrawer();
    
    void setRectangle(const ofRectangle& rectangle);
    
    void drawWave(float *array);
    
private:
    
    ofRectangle mRectangle;
    
};