/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SceneLissajous.h"

//tmp value
float _cycle = 0;

SceneLissajous::SceneLissajous()
{
    mEzCam.setDistance(100);
    
    mNumPoints = (int)(NUM_SAMPLES / 3);
    mPts.resize(NUM_3D_POINTS, vector<ofVec3f>(BUFFER_SIZE));
}

SceneLissajous::~SceneLissajous()
{
}

void SceneLissajous::setup()
{
    switch (mVariation) {
        default:
        case 0: setup_variation_1(); break;
        case 1: setup_variation_2(); break;
    }
    
}

void SceneLissajous::update()
{
    // サンプルからリサジュー図形を計算
    for (int i = 0; i < NUM_3D_POINTS; i++) {
        mScopeMappingInterpreter->get3dLissajousPoints(mSamples[i*3],
                                                       mSamples[i*3+1],
                                                       mSamples[i*3+2],
                                                       mPts[i],
                                                       100);
    }
    
    switch (mVariation)
    {
        default:
        case 0: update_variation_1(); break;
        case 1: update_variation_2(); break;
    }
    
}

void SceneLissajous::draw()
{
    switch (mVariation) {
        default:
        case 0: draw_variation_1(); break;
        case 1: draw_variation_2(); break;
    }
}

//-------------------------------------------------------------------- variation 1

void SceneLissajous::setup_variation_1()
{
    mCam.setPosition(0, 0, 100);
    mCamLook.set(0, 0, 0);
    mCamPosition.set(0, 0, 100);
    mCamCalibratePosition.set(0, 0, 0);
}

void SceneLissajous::update_variation_1()
{
    //TODO: fps依存じゃなくて秒数でインクリメントするようにする
    float c = (float)(ofGetFrameNum() % 1000) / 1000;
    float vec = c * (PI * 2);
    float x = sin(vec) * (200 + mCamCalibratePosition.x);
    float z = cos(vec) * (200 + mCamCalibratePosition.z);
    mCamPosition.set(x, 35 + mCamCalibratePosition.y, z);
    mCam.lookAt(mCamLook);
    mCam.setPosition(mCamPosition);
}

void SceneLissajous::draw_variation_1()
{
    cameraBegin();
    ofBackground(0, 0, 0);
    
    ofFill();
    
    ofSetColor(40);
    mSamplePointsDrawer->drawAsix(10000);
    
    
    ofSetColor(235, 220, 255);
    mSamplePointsDrawer->drawBox(mPts[0], 0.3);
    
    ofSetColor(255, 80, 220);
//    mSamplePointsDrawer->drawBox(mPts[1], 0.3);
    
    
    
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XZ);
    mSamplePointsDrawer->set2dDistance(-75);
    
    //    ofSetColor(127, 255, 127);
    //  mSamplePointsDrawer->draw3dTo2dJointLines(mPts, true);
    
    //    ofSetColor(255, 255, 255);
    //    mSamplePointsDrawer->drawGrid(100, 15);
    
    //    mSamplePointsDrawer->drawDebug();
    cameraEnd();

}

//-------------------------------------------------------------------- variation 2

void SceneLissajous::setup_variation_2()
{
    mCamLook.set(0,0,0);
    mCamPosition.set(0,0, 150);
}

void SceneLissajous::update_variation_2()
{
    mCam.lookAt(mCamLook);
    mCam.setPosition(mCamPosition);
}

void SceneLissajous::draw_variation_2()
{
    ofBackground(255, 255, 255);
    ofSetLineWidth(1);
    
    // draw waves
    ofSetColor(0);
    ofNoFill();
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        //        mSamplePointsDrawer->drawWave(mSamples[i],
        //                                      ofVec3f(-ofGetWidth()/2, 0, 0), ofVec3f(ofGetWidth(), 0, 0), 100);
        mSamplePointsDrawer->drawWave(mSamples[i], ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    }
    
    cameraBegin();
    
    //grid lines
    ofSetColor(220);
    mSamplePointsDrawer->drawGrid(200, 60, 0, BaseScopeManager::TO2D_XY);
    ofSetColor(180);
    mSamplePointsDrawer->drawGrid(200, 30, 0, BaseScopeManager::TO2D_XY);
    ofSetColor(0);
    mSamplePointsDrawer->drawAsixX(3000);
    mSamplePointsDrawer->drawAsixY(3000);
    
    // draw points
    ofFill();
    mSamplePointsDrawer->drawCircle(mPts[0], 0.3);
    
//    ofSetColor(255, 80, 220);
//    mSamplePointsDrawer->drawBox(mPts[1], 0.3);
    
//    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XZ);
//    mSamplePointsDrawer->set2dDistance(-75);
    
    cameraEnd();
}


