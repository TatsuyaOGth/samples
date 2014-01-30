/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "SceneMatrix.h"

SceneMatrix::SceneMatrix()
{
}

SceneMatrix::~SceneMatrix()
{
}

void SceneMatrix::setup()
{
}

void SceneMatrix::update()
{
}

void SceneMatrix::draw()
{
    ofBackground(0);
    
    // draw frequency brightness
    ofFill();
    float w = (float)ofGetWidth() / (float)NUM_SAMPLES;
    float h = (float)ofGetHeight() / (float)BUFFER_SIZE;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < BUFFER_SIZE; j++) {
            ofSetColor((unsigned char)((mSamples[i][j] + 1) * 127));
            ofRect((i * w), (j * h), (w/2), h);
        }
    }
    
    // draw raw data num
    ofSetColor(255);
    int rowspace = 16;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (j * rowspace > ofGetHeight()) break;
//            ofDrawBitmapString(ofToString(mSamples[i][j], 6), (i*w) + (w/2) + 12, (j * rowspace)); // raw
//            ofDrawBitmapString(ofToBinary(mSamples[i][j]), (i * w) + 20, (j * rowspace)); // binary
            ofDrawBitmapString(ofToHex(mSamples[i][j]), (i*w) + (w/2) + 12, (j * rowspace)); // hex
        }
    }
    
    // draw waves
    ofNoFill();
//    ofSetColor(255, 0, 0);
    for (int i = 0; i < NUM_SAMPLES; i++) {
//    mSamplePointsDrawer->drawWave(mSamples[i],
//                                  ofVec3f(0, ofGetHeight()/2, 0),
//                                  ofVec3f(ofGetWidth(), ofGetHeight()/2, 0),
//                                  ofGetHeight()/2
//                                  );
        mSamplePointsDrawer->drawWaveZeroClear(mSamples[i],
                                               ofVec3f(0, ofGetHeight()/2, 0),
                                               ofVec3f(ofGetWidth(), ofGetHeight()/2, 0),
                                               ofColor(255,0,0),
                                               ofGetHeight()/2
                                               );
    }
}

void SceneMatrix::keyPressed(int key)
{
}

void SceneMatrix::cue(const int cue)
{
}
