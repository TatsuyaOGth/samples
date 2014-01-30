/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SamplePointsDrawer.h"

SamplePointsDrawer::SamplePointsDrawer():
m2dDistance(0),
mTo2dMode(TO2D_XY)
{
    mMesh.setMode(OF_PRIMITIVE_POINTS);
}

SamplePointsDrawer::~SamplePointsDrawer()
{
}

//=============================================================

void SamplePointsDrawer::drawWave(const float *src, const ofRectangle rect)
{
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(((float)i / (float)BUFFER_SIZE) * rect.width + rect.x,
                 (src[i] * (rect.height / 2)) + (rect.height / 2) + rect.y);
    }
    ofEndShape(false);
}

void SamplePointsDrawer::drawWave(const float *src, const ofVec3f &p1, const ofVec3f &p2, const float amp)
{
    ofPushMatrix();
    ofTranslate(p1);
    
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        // TODO: p2はp1との相対距離
        ofVertex(p1.x + ((p2.x - p1.x) / (float)BUFFER_SIZE) * i,
                 src[i] * amp,
                 p1.z + ((p2.z - p1.z) / (float)BUFFER_SIZE) * i);
    }
    ofEndShape(false);
    ofPopMatrix();
}

void SamplePointsDrawer::drawWaveZeroClear(const float *src, const ofVec3f &p1, const ofVec3f &p2, const ofColor& col, const float amp)
{
    ofPushMatrix();
    ofTranslate(p1);

    ofMesh wigglyMeshLine;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        // サンプルが０に近づくほど透明にする
//        ofSetColor(col, (unsigned char)(abs(src[i]*255)));
        // TODO: p2はp1との相対距離
//        ofVertex(p1.x + ((p2.x - p1.x) / (float)BUFFER_SIZE) * i,
//                 src[i] * amp,
//                 p1.z + ((p2.z - p1.z) / (float)BUFFER_SIZE) * i);
        wigglyMeshLine.addColor(ofFloatColor(255));
        ofVec3f vec(p1.x + ((p2.x - p1.x) / (float)BUFFER_SIZE) * i,
                    src[i] * amp,
                    p1.z + ((p2.z - p1.z) / (float)BUFFER_SIZE) * i
                    );
        wigglyMeshLine.addVertex(vec);
    }
//    wigglyMeshLine.draw();
//    wigglyMeshLine.drawVertices();
//    wigglyMeshLine.drawWireframe();
    wigglyMeshLine.drawFaces();
    ofPopMatrix();
}

//=============================================================


void SamplePointsDrawer::drawJointLines(ofVec3f *pts, const bool jointBeginToEnd)
{
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(pts[i]);
    }
    ofEndShape(jointBeginToEnd);
}

void SamplePointsDrawer::drawBox(const ofVec3f *pts, const float size)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(pts[i]);
        ofDrawBox(-size/2, -size/2, -size/2, size);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::drawBox(const vector<ofVec3f>& pts, const float size)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(pts[i]);
        ofDrawBox(-size/2, -size/2, -size/2, size);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::drawCircle(const vector<ofVec3f>& pts, const float radius)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(pts[i]);
        ofCircle(-radius/2, -radius/2, 0, radius);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::drawRect(const vector<ofVec3f> &pts, const float x, const float y)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(pts[i]);
        ofRect(-x/2, -y/2, 0, x, y);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::drawPoints(const vector<ofVec3f> &pts, const ofColor& col, const float size)
{
    mMesh.clear();
    for (int i = 0; i < pts.size(); i++)
    {
        mMesh.addColor(col);
        mMesh.addVertex(pts[i]);
    }
    glPointSize(size);
    mMesh.draw();
}

//=============================================================

void SamplePointsDrawer::set2dDistance(const float _distance)
{
    m2dDistance = _distance;
}

void SamplePointsDrawer::setTo2dMode(const to2dMode mode)
{
    mTo2dMode = mode;
}

ofVec3f& SamplePointsDrawer::convert2dVec(const ofVec3f &pts)
{
    switch (mTo2dMode) {
        case TO2D_XY: mConverted2dVec.set(pts.x, pts.y, m2dDistance); break;
        case TO2D_YZ: mConverted2dVec.set(m2dDistance, pts.y, pts.z); break;
        case TO2D_XZ: mConverted2dVec.set(pts.x, m2dDistance, pts.z); break;
    }
    return mConverted2dVec;
}

void SamplePointsDrawer::draw3dTo2dBox(const ofVec3f *pts)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(ofPoint(convert2dVec(pts[i])));
        ofDrawBox(0, 0, 0, 0.1);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::draw3dTo2dBox(const vector<ofVec3f>& pts, const float size)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(ofPoint(convert2dVec(pts[i])));
        ofDrawBox(0, 0, 0, size);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::draw3dTo2dRect(const vector<ofVec3f> &pts, const float w, const float h)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(ofPoint(convert2dVec(pts[i])));
        ofRect(-w/2, -h/2, w*2, h*2);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::draw3dTo2dCircle(const vector<ofVec3f> &pts, const float radius)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofPushMatrix();
        ofTranslate(ofPoint(convert2dVec(pts[i])));
        ofCircle(0, 0, radius);
        ofPopMatrix();
    }
}

void SamplePointsDrawer::draw3dTo2dJointLines(const ofVec3f *pts, const bool jointBeginToEnd)
{
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(convert2dVec(pts[i]));
    }
    ofEndShape(jointBeginToEnd);
}

void SamplePointsDrawer::draw3dTo2dJointLines(const vector<ofVec3f>& pts, const bool jointBeginToEnd)
{
    ofBeginShape();
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofVertex(convert2dVec(pts[i]));
    }
    ofEndShape(jointBeginToEnd);
}

void SamplePointsDrawer::draw3dTo2dLine(const ofVec3f *pts)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        ofLine(pts[i], convert2dVec(pts[i]));
    }
}

void SamplePointsDrawer::draw3dTo2dPoints(const vector<ofVec3f> &pts, const ofColor &col, const float size)
{
    mMesh.clear();
    mMesh.setMode(OF_PRIMITIVE_POINTS);
    for (int i = 0; i < pts.size(); i++)
    {
        mMesh.addColor(col);
        mMesh.addVertex(convert2dVec(pts[i]));
    }
    glPointSize(size);
    mMesh.draw();
}

//============================================================= mesh

ofMesh& SamplePointsDrawer::getMesh()
{
    return mMesh;
}

//============================================================= asix

void SamplePointsDrawer::drawAsix(const float size)
{
    drawAsixX(size);
    drawAsixY(size);
    drawAsixZ(size);
}

void SamplePointsDrawer::drawAsixX(const float size)
{
    ofLine(-(size/2), 0, 0, (size/2), 0, 0);
}

void SamplePointsDrawer::drawAsixY(const float size)
{
    ofLine(0, -(size/2), 0, 0, (size/2), 0);
}

void SamplePointsDrawer::drawAsixZ(const float size)
{
    ofLine(0, 0, -(size/2), 0, 0, (size/2));
}

//------------------------------------------------------------

void SamplePointsDrawer::drawGrid(const float scale, const float ticks)
{
    drawGrid(scale, ticks, m2dDistance, mTo2dMode);
}

void SamplePointsDrawer::drawGrid(const float scale, const float ticks, const float distance)
{
    drawGrid(scale, ticks, distance, mTo2dMode);
}

void SamplePointsDrawer::drawGrid(const float scale, const float ticks, const float distance, const to2dMode mode)
{
    ofPushMatrix();
    switch (mode)
    {
        case TO2D_XY:
            ofTranslate(0, 0, distance);
            ofRotate(90, 0, 1, 0);
            ofDrawGridPlane(scale, ticks, false);
            ofPopMatrix();
            break;
            
        case TO2D_YZ:
            ofTranslate(distance, 0, 0);
            ofDrawGridPlane(scale, ticks, false);
            break;
            
        case TO2D_XZ:
            ofTranslate(0, distance, 0);
            ofRotate(90, 0, 0, -1);
            ofDrawGridPlane(scale, ticks, false);
            break;
    }
    ofPopMatrix();
}

void SamplePointsDrawer::drawDebug()
{
    ofDrawAxis(10);
}
