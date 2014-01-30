/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "ofMain.h"
#include "Properties.h"
#include "ScopeMappingInterpreter.h"
#include "SamplePointsDrawer.h"

class BaseScene
{
public:
    
    BaseScene():
    mSamples(0),
    bManualCamera(false),
    mVariation(0),
    mScopeMappingInterpreter(ScopeMappingInterpreter::getInstance()),
    mSamplePointsDrawer(SamplePointsDrawer::getInstance())
    {};
    virtual ~BaseScene(){};
    
    // main method
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void keyPressed(int key) = 0; ///< キー入力設定（AppCore.cpp優先）
    virtual void cue(const int cue) = 0; ///< キューを送る用
    
    // shere method
    void setVariation(const unsigned char variation);
    void setNextVariation();
    void setPreviousVariation();
    void setManualCamera(const bool bManual);
    void toggleManualCamera();
    
    void setAudioSamples(float (*samples)[BUFFER_SIZE]);
    
protected:
    
    // shere method
    void cameraBegin();
    void cameraEnd();
    
    //sample data（２重配列のポインタ）
    float (*mSamples)[BUFFER_SIZE];
    
    // module
    ScopeMappingInterpreter * mScopeMappingInterpreter;
    SamplePointsDrawer * mSamplePointsDrawer;
    
    // camera
    ofEasyCam mEzCam;
    ofCamera mCam;
    bool bManualCamera;
    
    // variation
    unsigned char mVariation;
};
