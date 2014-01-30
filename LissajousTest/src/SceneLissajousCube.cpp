/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "SceneLissajousCube.h"

//tmp values
ofVec3f _horiRollPos(0, 0, 100);
float _c = 0; //カメラ回転

SceneLissajousCube::SceneLissajousCube()
{
    // camera
    mEzCam.setDistance(100);
    mCam.setPosition(0, 0, 150);
    mCamLook.set(0, 0, 0);
    mCamPosition.set(0, 0, 150);
    mCameraMode = STABLE;
    mCamSpeed = 0.001; //TODO: カメラのスピード
    
    // grid
    mBaseDistans = 75;
    mBaseGridScale = mBaseDistans;
    mBaseGridTicks = 15;

    
    mNumPoints = (int)(NUM_SAMPLES / 3);
    mPts.resize(NUM_3D_POINTS, vector<ofVec3f>(BUFFER_SIZE));
    bZoom = false;
    
}

SceneLissajousCube::~SceneLissajousCube()
{
}

void SceneLissajousCube::setup()
{
//    mCam.setPosition(0, 0, 100);
//    mCamLook.set(0, 0, 0);
//    mCamPosition.set(0, 0, 100);
//    
//    mBaseDistans = 75;
//    mBaseGridScale = mBaseDistans;
//    mBaseGridTicks = 15;
}

void SceneLissajousCube::update()
{
    // サンプルからリサジュー図形を計算
    for (int i = 0; i < NUM_3D_POINTS; i++) {
        mScopeMappingInterpreter->get3dLissajousPoints(mSamples[i*3],
                                                       mSamples[i*3+1],
                                                       mSamples[i*3+2],
                                                       mPts[i],
                                                       mBaseDistans*0.9);
    }
    
    updateCamera();
}

void SceneLissajousCube::draw()
{
    ofBackgroundGradient(ofColor(32), ofColor(0), OF_GRADIENT_LINEAR);
    

    
    cameraBegin();
    
    ofFill();
    
//    ofSetColor(80);
//    mSamplePointsDrawer->drawAsix(200);
    
    // Lissajous Points
    ofSetColor(255);
//    mSamplePointsDrawer->drawBox(mPts[0], 0.3);
    mSamplePointsDrawer->drawPoints(mPts[0], ofColor(255), 2);
    

    // 2D mapping
    mSamplePointsDrawer->set2dDistance(-mBaseDistans);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XZ);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(127,0,0), 2);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XY);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(0,127,0), 2);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_YZ);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(0,0,127), 2);
    mSamplePointsDrawer->set2dDistance(mBaseDistans);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XZ);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(127,0,0), 2);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_XY);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(0,127,0), 2);
    mSamplePointsDrawer->setTo2dMode(BaseScopeManager::TO2D_YZ);
    mSamplePointsDrawer->draw3dTo2dPoints(mPts[0], ofColor(0,0,127), 2);


//    mSamplePointsDrawer->draw3dTo2dCircle(mPts[0], 0.5);
    
    drawGridCube(mBaseDistans, mBaseGridTicks, ofColor(127, 32));
    drawGridCube(mBaseDistans, mBaseGridTicks*2, ofColor(127, 18));
    
    //mSamplePointsDrawer->drawDebug();
    cameraEnd();
    
}

void SceneLissajousCube::cue(const int cue)
{
    switch (cue) {
        case 0: setup(); break;
        case 1:
            mCameraMode = STABLE;
            break;
        case 2:
            mCameraMode = HORIZON_ROLL_RIGHT;
            break;
        case 3:
            mCameraMode = STABLE_FRONT;
            break;
        case 4:
        {
            float rndx = ofRandom(-200, 200);
            float rndy = ofRandom(-200, 200);
            float rndz = ofRandom(-200, 200);
            mTargerPos.set(rndx, rndy, rndz);
            mCameraMode = RANDOM_POSITION;
        }
            break;
        case 5:
            bZoom = !bZoom;
            break;
            
        default:
            break;
    }
}


//--------------------------------------------------------

void SceneLissajousCube::interpolatePosition(ofVec3f *updatePos, const ofVec3f &targetPos, const float denomirator)
{
//    if (updatePos->distance(targetPos) > 0.01)
//    {
        // TODO: 補完を線形移動にしたい
        *updatePos -= (*updatePos - targetPos) / denomirator;
//    }
//    else
//    {
//        updatePos->set(targetPos);
//    }
}

void SceneLissajousCube::updateCamera()
{
    switch (mCameraMode) {
        case STABLE: /* void */ break;
            
        case HORIZON_ROLL_RIGHT:
        {
            float c = _c + mCamSpeed;
            c = MIN_NORM(c, 1);
            float vec = c * (PI * 2);
            float x = sin(vec) * 200;
            float z = cos(vec) * 200;
            _horiRollPos.set(x, 35, z);
            _c = c;
            // whith interpolate
            interpolatePosition(&mCamPosition, _horiRollPos, 10);
//            mCamPosition = _horiRollPos;
        }
            break;
        case STABLE_FRONT:
        {
            interpolatePosition(&mCamPosition, ofVec3f(0, 0, mBaseDistans*2), 10);
            mCamLook.set(0, 0, 0);
        }
            break;
        case RANDOM_POSITION:
        {
            interpolatePosition(&mCamPosition, mTargerPos, 10);
            mCamLook.set(0, 0, 0);
        }
            break;
    }
    
    mCam.lookAt(mCamLook);
    mCam.setPosition(mCamPosition);
}

void SceneLissajousCube::drawGridCube(const float scale, const float ticks, const ofColor &col)
{
    ofSetColor(col);
    mSamplePointsDrawer->drawGrid(scale, ticks, scale, BaseScopeManager::TO2D_XZ);
    mSamplePointsDrawer->drawGrid(scale, ticks, scale, BaseScopeManager::TO2D_XY);
    mSamplePointsDrawer->drawGrid(scale, ticks, scale, BaseScopeManager::TO2D_YZ);
    mSamplePointsDrawer->drawGrid(scale, ticks, -scale, BaseScopeManager::TO2D_XZ);
    mSamplePointsDrawer->drawGrid(scale, ticks, -scale, BaseScopeManager::TO2D_XY);
    mSamplePointsDrawer->drawGrid(scale, ticks, -scale, BaseScopeManager::TO2D_YZ);
}

