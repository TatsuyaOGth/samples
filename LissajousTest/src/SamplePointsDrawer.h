/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScopeManager.h"

class SamplePointsDrawer : public virtual BaseScopeManager
{
public:

    static SamplePointsDrawer * getInstance()
    {
        static SamplePointsDrawer instance;
        return &instance;
    }
    
    ~SamplePointsDrawer();
    
    // drawing array
    void drawWave(const float src[], const ofRectangle rect);
    void drawWave(const float src[], const ofVec3f& p1, const ofVec3f& p2, const float amp);
    void drawWaveZeroClear(const float src[], const ofVec3f& p1, const ofVec3f& p2, const ofColor& col, const float amp);
    
    // drawing sample points
    void drawJointLines(ofVec3f pts[], const bool jointBeginToEnd = false);
    void drawBox(const ofVec3f pts[], const float size);
    void drawBox(const vector<ofVec3f>& pts, const float size);
    void drawCircle(const vector<ofVec3f>& pts, const float radius);
    void drawRect(const vector<ofVec3f>& pts, const float x, const float y);
    void drawPoints(const vector<ofVec3f>& pts, const ofColor& col, const float size);
    
    // 2d mapping
    void set2dDistance(const float disrance);
    void setTo2dMode(const to2dMode mode);
    void draw3dTo2dBox(const ofVec3f pts[]);
    void draw3dTo2dBox(const vector<ofVec3f>& pts, const float size);
    void draw3dTo2dRect(const vector<ofVec3f>& pts, const float w, const float h);
    void draw3dTo2dCircle(const vector<ofVec3f>& pts, const float radius);
    void draw3dTo2dJointLines(const ofVec3f pts[], const bool jointBeginToEnd = false);
    void draw3dTo2dJointLines(const vector<ofVec3f>& pts, const bool jointBeginToEnd = false);
    void draw3dTo2dLine(const ofVec3f pts[]);
    void draw3dTo2dPoints(const vector<ofVec3f>& pts, const ofColor& col, const float size);
    
    // mesh
    ofMesh& getMesh();
    
    // asix
    void drawAsix(const float size);
    void drawAsixX(const float size);
    void drawAsixY(const float size);
    void drawAsixZ(const float size);
    
    // grid
    void drawGrid(const float scale, const float ticks);
    void drawGrid(const float scale, const float ticks, const float distance);
    void drawGrid(const float scale, const float ticks, const float distance, const to2dMode mode);
    
    void drawDebug();
    
private:
    
    // Singleton
    SamplePointsDrawer();
    SamplePointsDrawer(const SamplePointsDrawer& spd);
    SamplePointsDrawer& operator=(const SamplePointsDrawer& spd);
    
    ofVec3f& convert2dVec(const ofVec3f& pts);
    
    
    ofVec3f mConverted2dVec;
    ofMesh mMesh;
    
    float m2dDistance;
    to2dMode mTo2dMode;
};
