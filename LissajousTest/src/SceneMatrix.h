/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "BaseScene.h"

class SceneMatrix : public BaseScene
{
public:
    
    SceneMatrix();
    virtual ~SceneMatrix();
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void cue(const int cue);
    
private:
    
    
    
};
