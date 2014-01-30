/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScopeManager.h"

class ScopeMappingInterpreter : public virtual BaseScopeManager
{
public:
    
    ~ScopeMappingInterpreter();
    
    // get instance
    static ScopeMappingInterpreter * getInstance()
    {
        static ScopeMappingInterpreter instance;
        return &instance;
    }
    
    void getWavePoints(const float src[], ofVec3f dst[], const ofRectangle rect);
    void get2dLissajousPoints(const float srcX[], const float srcY[], ofVec3f dst[], const float amp=1);
    void get3dLissajousPoints(const float srcX[], const float srcY[], const float srcZ[], ofVec3f dst[], const float amp=1);
    void get3dLissajousPoints(const float srcX[], const float srcY[], const float srcZ[], vector<ofVec3f>& dst, const float amp=1);
    
    void rotateToMinTop(float src[]);
    
    ofVec2f convert2dVec(const ofVec3f& src, const to2dMode& mode);
    float convert2dVecX(const ofVec3f& src, const to2dMode& mode);
    float convert2dVecY(const ofVec3f& src, const to2dMode& mode);
    
    void getCycleOfAngleArray(const ofVec3f *src, vector<float> &dst, const to2dMode& mode);
    
    // detect vertex of points
    vector<ofVec2f>& getVertex4(vector<ofVec3f>& src); //2D rect
    vector<ofVec3f>& getVertex8(vector<ofVec3f>& src); //3D box
    
private:
    
    // Singleton
    ScopeMappingInterpreter();
    ScopeMappingInterpreter(const ScopeMappingInterpreter& smi);
    ScopeMappingInterpreter& operator=(const ScopeMappingInterpreter& smi);
    
    // retern values
    ofVec2f mComverded2dVec;
    vector<ofVec2f> mVertex4;
    vector<ofVec3f> mVertex8;
    
};
