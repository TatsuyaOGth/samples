/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SceneTest.h"

void SceneTest::setup()
{
    mSamples = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        mPts[i].set(0, 0, 0);
    }
}

void SceneTest::update()
{
    
//    ofRectangle rect = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
//    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
//    {
//        mPts[i] = ofPoint(((float)i / (float)BUFFER_SIZE) * rect.width + rect.x,
//                         mSamples[0][i] * (rect.height/2) + rect.y);
//    }
    
    mScopeMappingInterpreter->get2dLissajousPoints(mSamples[0], mSamples[1], mPts, 600);
    
}

void SceneTest::draw()
{
    ofSetColor(255, 255, 255);
    ofNoFill();
    
    /*
    ofRectangle mRectangle = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(((float)i / (float)BUFFER_SIZE) * mRectangle.width + mRectangle.x,
                 (mSamples[0][i] * (mRectangle.height / 2)) + (mRectangle.height / 2) + mRectangle.y);
    }
    ofEndShape(false);
    
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(((float)i / (float)BUFFER_SIZE) * mRectangle.width + mRectangle.x,
                 (mSamples[1][i] * (mRectangle.height / 2)) + (mRectangle.height / 2) + mRectangle.y);
    }
    ofEndShape(false);
    */
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(mPts[i]);
        ofDrawBox(0, 0, 0, 0.1);
        ofPopMatrix();
    }
    
    mSamplePointsDrawer->drawWaveZeroClear(mSamples[0],
                                           ofVec3f(0, ofGetHeight()/2, 0),
                                           ofVec3f(ofGetWidth(), ofGetHeight()/2, 0),
                                           ofColor(255),
                                           ofGetHeight()/2
                                           );
    
}