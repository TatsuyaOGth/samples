/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScene.h"

class SceneWave : public BaseScene
{
public:
    
    SceneWave();
    virtual ~SceneWave();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key){};
    void cue(const int cue){};
    
private:
    
    void drawWave(float * array);
    
    ofRectangle mRectangle;
    ofColor mCol;
    
};