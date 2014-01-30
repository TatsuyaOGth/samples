/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SceneWave.h"

SceneWave::SceneWave()
{
    mRectangle.set(0, 0, ofGetWidth(), ofGetHeight());
}

SceneWave::~SceneWave()
{
}

void SceneWave::setup()
{
    mCol.setHue(0);
    mCol.setBrightness(225);
    mCol.setSaturation(127);
}

void SceneWave::update()
{
//    mScopeMappingInterpreter->getWavePoints(mSamples[0], mPts, ofRectangle(0, ofGetHeight()/2, ofGetWidth(), ofGetHeight()/2));
    mRectangle.set(0, 0, ofGetWidth(), ofGetHeight());
}

void SceneWave::draw()
{
    ofNoFill();
    
    
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        mCol.setHue(ofMap(i, 0, NUM_SAMPLES, 0, 255));
        ofSetColor(mCol);
        drawWave(mSamples[i]);
    }
}

void SceneWave::drawWave(float *array)
{
    mSamplePointsDrawer->drawWave(array,
                                  ofVec3f(0, ofGetHeight()/2, 0),
                                  ofVec3f(ofGetWidth(), ofGetHeight()/2, 0),
                                  ofGetHeight());
}
