/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SceneWhiteNote.h"

//tmp value
float _cycle = 0;

SceneWhiteNote::SceneWhiteNote()
{
    mEzCam.setDistance(100);
    
    mNumPoints = (int)(NUM_SAMPLES / 3);
    mPts.resize(NUM_3D_POINTS, vector<ofVec3f>(BUFFER_SIZE));
}

SceneWhiteNote::~SceneWhiteNote()
{
}

void SceneWhiteNote::setup()
{
    ofSetCircleResolution(80);
    mCamLook.set(0,0,0);
    mCamPosition.set(0,0, 150);
}

void SceneWhiteNote::update()
{
    // サンプルからリサジュー図形を計算
    for (int i = 0; i < NUM_3D_POINTS; i++) {
        mScopeMappingInterpreter->get3dLissajousPoints(mSamples[i*3],
                                                       mSamples[i*3+1],
                                                       mSamples[i*3+2],
                                                       mPts[i],
                                                       100);
    }
    mCam.lookAt(mCamLook);
    mCam.setPosition(mCamPosition);
}

void SceneWhiteNote::draw()
{
    ofBackground(255, 255, 255);
    ofSetLineWidth(1);

    
    // draw waves
    ofSetColor(0);
    ofNoFill();
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        mSamplePointsDrawer->drawWave(mSamples[i], ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    }
    
    cameraBegin(); //------------------------ camera begin
    
    //grid lines
    drawGridLines();
    
    // draw points
    ofFill();
    ofSetColor(0);
//    mSamplePointsDrawer->drawCircle(mPts[0], 0.3);
    mSamplePointsDrawer->drawPoints(mPts[0], ofColor(0), 2);

    
//    ofSetColor(255, 0, 0);
//    mSamplePointsDrawer->drawCircle(mPts[1], 0.3);
    
//    mSamplePointsDrawer->drawCircle(mPts[2], 0.3);
    
//    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XZ);
//    mSamplePointsDrawer->set2dDistance(-75);
    
    cameraEnd(); //--------------------------- camera end
    
    //ruler lines
    drawRulerLines();
}

void SceneWhiteNote::drawGridLines()
{
    ofSetColor(220);
    mSamplePointsDrawer->drawGrid(200, 60, 0, BaseScopeManager::TO2D_XY);
    ofSetColor(180);
    mSamplePointsDrawer->drawGrid(200, 30, 0, BaseScopeManager::TO2D_XY);
    ofSetColor(127);
    mSamplePointsDrawer->drawAsixX(400);
    mSamplePointsDrawer->drawAsixY(400);
}

void SceneWhiteNote::drawRulerLines()
{
    ofNoFill();
//    ofSetColor(0);
//    // circle line
//    ofCircle(CENTER_X, CENTER_Y, ofGetHeight() / 2);
//    // cross lines
//    ofLine(0, 0, ofGetWidth(), ofGetHeight());
//    ofLine(ofGetWidth(), 0, 0, ofGetHeight());
//    // rulerz	float	-2.0660198	-2.0660198
//    ofSetColor(220);
//    for (int i = 0; i < ofGetWidth(); i += 5) ofLine(i, 0, i, 5);
//    for (int i = 0; i < ofGetHeight(); i += 5) ofLine(0, i, 5, i);
//    ofSetColor(64);
//    for (int i = 0; i < ofGetWidth(); i += 25) ofLine(i, 0, i, 8);
//    for (int i = 0; i < ofGetHeight(); i += 25) ofLine(0, i, 8, i);
    
    // samples centroid
//    ofSetColor(255, 0, 0);
//    ofVec3f vec = mSamplePointsDrawer->getMesh().getCentroid();
//    ofPushMatrix();
//    ofTranslate(CENTER_X, CENTER_Y);
//    ofCircle(vec.x * 5, -vec.y * 5, 50);
//    ofPopMatrix();

}

