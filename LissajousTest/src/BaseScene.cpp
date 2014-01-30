/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "BaseScene.h"

void BaseScene::setAudioSamples(float (*samples)[BUFFER_SIZE])
{
    mSamples = samples;
}

void BaseScene::cameraBegin()
{
    if (bManualCamera)
        mEzCam.begin();
    else
        mCam.begin();
}

void BaseScene::cameraEnd()
{
    if (bManualCamera)
        mEzCam.end();
    else
        mCam.end();
}

void BaseScene::setManualCamera(const bool bManual)
{
    bManualCamera = bManual;
}

void BaseScene::toggleManualCamera()
{
    bManualCamera = !bManualCamera;
}

void BaseScene::setVariation(const unsigned char variation)
{
    if (variation > 0)
    {
        mVariation = variation;
    }
}

void BaseScene::setNextVariation()
{
    mVariation++;
}

void BaseScene::setPreviousVariation()
{
    mVariation--;
}
