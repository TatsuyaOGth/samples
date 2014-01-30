#pragma once

#include "BaseScene.h"

class SceneWhiteNote : public BaseScene
{
public:
    
    SceneWhiteNote();
    virtual ~SceneWhiteNote();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key){};
    void cue(const int cue){};
    
private:
    
    void drawGridLines();
    void drawRulerLines();
    
    vector<vector<ofVec3f> > mPts;
    int mNumPoints;
    
    //camera
    ofVec3f mCamLook;
    ofVec3f mCamPosition;
    ofVec3f mCamCalibratePosition;
};
