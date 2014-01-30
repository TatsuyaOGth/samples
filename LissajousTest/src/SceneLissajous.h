/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScene.h"

class SceneLissajous : public BaseScene
{
public:
    
    SceneLissajous();
    virtual ~SceneLissajous();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key){};
    void cue(const int cue){};
    
private:
    
    void setup_variation_1(); ///< test
    void update_variation_1();
    void draw_variation_1();
    
    void setup_variation_2(); ///<---------------- scene 1
    void update_variation_2();
    void draw_variation_2();
    
    vector<vector<ofVec3f> > mPts;
    int mNumPoints;
    
    //camera
    ofVec3f mCamLook;
    ofVec3f mCamPosition;
    ofVec3f mCamCalibratePosition;
};