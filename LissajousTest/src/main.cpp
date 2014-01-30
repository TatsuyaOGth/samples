/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */

#include "ofMain.h"
#include "testApp.h"

int main( )
{
	ofSetupOpenGL(1024,768,OF_WINDOW);
	ofRunApp(new testApp());
}
