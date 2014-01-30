/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "ScopeMappingInterpreter.h"

ScopeMappingInterpreter::ScopeMappingInterpreter()
{
}

ScopeMappingInterpreter::~ScopeMappingInterpreter()
{
}

void ScopeMappingInterpreter::getWavePoints(const float src[], ofVec3f dst[], const ofRectangle rect)
{
    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        dst[i] = ofPoint(((float)i / (float)BUFFER_SIZE) * rect.width + rect.x,
                         src[i] * (rect.height/2) + rect.y);
    }
}

void ScopeMappingInterpreter::get2dLissajousPoints(const float *srcX, const float *srcY, ofVec3f *dst, const float amp)
{
    float x = 0;
    float y = 0;
    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        x = sin(srcX[i]) * amp;
        y = sin(srcY[i]) * amp;
        dst[i].set(x, y, 0);
    }
}

void ScopeMappingInterpreter::get3dLissajousPoints(const float *srcX, const float *srcY, const float *srcZ, ofVec3f *dst, const float amp)
{
    float x = 0;
    float y = 0;
    float z = 0;
    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        x = sin(srcX[i]) * amp;
        y = sin(srcY[i]) * amp;
        z = sin(srcZ[i]) * amp;
        dst[i].set(x, y, z);
    }
}

void ScopeMappingInterpreter::get3dLissajousPoints(const float *srcX, const float *srcY, const float *srcZ, vector<ofVec3f> &dst, const float amp)
{
    float x = 0;
    float y = 0;
    float z = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        x = sin(srcX[i]) * amp;
        y = sin(srcY[i]) * amp;
        z = sin(srcZ[i]) * amp;
        dst[i].set(x, y, z);
    }
}

void ScopeMappingInterpreter::rotateToMinTop(float *src)
{
    // get min index
    float min = 1.0f;
    int minId = 0;
    for (unsigned int i = 0; i < BUFFER_SIZE; i++)
    {
        if (abs(src[i]) < min) {
            min = abs(src[i]);
            minId = i;
        }
    }
    // rotate array
    rotate(src, src + minId, src + BUFFER_SIZE);
}

ofVec2f ScopeMappingInterpreter::convert2dVec(const ofVec3f &src, const to2dMode &mode)
{
    switch (mode) {
        case TO2D_XY: return ofVec2f(src.x, src.y);
        case TO2D_YZ: return ofVec2f(src.y, src.z);
        case TO2D_XZ: return ofVec2f(src.x, src.z);
    }
}

float ScopeMappingInterpreter::convert2dVecX(const ofVec3f &src, const to2dMode &mode)
{
    switch (mode) {
        case TO2D_XY: return src.x;
        case TO2D_YZ: return src.y;
        case TO2D_XZ: return src.x;
    }
}

float ScopeMappingInterpreter::convert2dVecY(const ofVec3f &src, const to2dMode &mode)
{
    switch (mode) {
        case TO2D_XY: return src.y;
        case TO2D_YZ: return src.z;
        case TO2D_XZ: return src.z;
    }
}

void ScopeMappingInterpreter::getCycleOfAngleArray(const ofVec3f *src, vector<float> &dst, const to2dMode &mode)
{
    assert(dst.size() == BUFFER_SIZE);
    
    float tx = convert2dVecX(src[0], mode);
    float ty = convert2dVecY(src[0], mode);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        float sx = convert2dVecX(src[i], mode);
        float sy = convert2dVecY(src[i], mode);
        double rnd = atan2((double)(sy - ty), (double)(sx - tx));
        float tmp = sin(rnd);
        dst[i] = tmp;
        tx = sx;
        ty = sy;
    }
}


//TODO: リサジューから頂点の取得
vector<ofVec2f>& ScopeMappingInterpreter::getVertex4(vector<ofVec3f> &src)
{
    mVertex4.resize(4, ofVec2f());
    for (vector<ofVec3f>::iterator it = src.begin(); it != src.end(); it++)
    {
        
    }
    return mVertex4;
}

//TODO: リサジューから頂点の取得
vector<ofVec3f>& ScopeMappingInterpreter::getVertex8(vector<ofVec3f> &src)
{
    return mVertex8;
}
