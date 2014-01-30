/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScene.h"

class SceneLissajousCube : public BaseScene
{
public:
    
    SceneLissajousCube();
    virtual ~SceneLissajousCube();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key){};
    void cue(const int cue);
    
private:
    
    void interpolatePosition(ofVec3f* updatePos, const ofVec3f& targetPos, const float denomirator = 10);
    void updateCamera();
    void drawGridCube(const float scale, const float ticks, const ofColor& col);
    
    // camera mode
    enum cameraMode
    {
        STABLE = 0, ///< 静止
        HORIZON_ROLL_RIGHT, ///< 水平方向右に回転
        STABLE_FRONT, ///< 正面で静止（距離補完あり）
        RANDOM_POSITION,
    } mCameraMode;
    
    vector<vector<ofVec3f> > mPts;
    int mNumPoints;
    
    //camera
    ofVec3f mCamLook;
    ofVec3f mCamPosition;
    float mCamSpeed;
    ofVec3f mTargerPos;
    
    float mBaseDistans;
    float mBaseGridScale;
    float mBaseGridTicks;
    
    bool bZoom;
    
};
