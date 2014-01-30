/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "ofMain.h"
#include "Properties.h"

class BaseScopeManager
{
public:
    
    BaseScopeManager(){};
    virtual ~BaseScopeManager(){};
    
    typedef enum {
        TO2D_XY = 0,
        TO2D_YZ,
        TO2D_XZ,
    } to2dMode;
    
protected:
        
};
