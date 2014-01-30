/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "AppCore.h"

void AppCore::setup(const int numOutChannels, const int numInChannels,
                    const int sampleRate, const int ticksPerBuffer)
{
    START_CLOCK;
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    ofDisableAntiAliasing();
//    ofSetFrameRate(60);
    
    //----------
    // setup Pd
    //----------
    if(!pd.init(numOutChannels, numInChannels, sampleRate, ticksPerBuffer)) {
		OF_EXIT_APP(1);
	}
    pd.addReceiver(*this);
    pd.addToSearchPath("pd");
    Patch patch = pd.openPatch("pd/main.pd");
    assert(patch.isValid());
	cout << patch << endl;
    pd.start();
    
    //----------
    // GUI setup
    //----------
    gui.setup();
    gui.add(mMasterVolume.setup("master vol.", 0.5, 0, 1));
    gui.loadFromFile("settings.xml");
    
    //----------
    // init values
    //----------
    bDebugMode = INIT_DEBUG_MODE;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < BUFFER_SIZE; j++) {
            mSamples[i][j] = 0;
        }
    }
    
    // setup scenes
    BaseScene * scene_0 = new SceneTest();
    BaseScene * scene_1 = new SceneWave();
    BaseScene * scene_2 = new SceneLissajous();
    BaseScene * scene_3 = new SceneWhiteNote();
    BaseScene * scene_4 = new SceneLissajousCube();
    BaseScene * scene_5 = new SceneMatrix();
    mScenes.push_back(scene_0);
    mScenes.push_back(scene_1);
    mScenes.push_back(scene_2);
    mScenes.push_back(scene_3);
    mScenes.push_back(scene_4);
    mScenes.push_back(scene_5);
    mCurrentScene = 0;
    mScenes[mCurrentScene]->setup();
    
//    mContoursWave.resize(pd.arraySize("contours_wave"));
    GET_CLOCK("setup time: ");
}

//--------------------------------------------------------------
void AppCore::update()
{
    mScenes[mCurrentScene]->setAudioSamples(mSamples);
    mScenes[mCurrentScene]->update();
    
    pd.sendFloat("master_vol", mMasterVolume);
}

//--------------------------------------------------------------
void AppCore::draw()
{
    if (bBlackOut) {
        ofBackground(0, 0, 0);
        return;
    }
    
    // TODO: fade background
    fadeBackground(ofColor(0, 0, 0, 255));
    
    mScenes[mCurrentScene]->draw();
    
    if (bDebugMode) {
        ofPushStyle();
        stringstream s;
        s << "fps: " << ofGetFrameRate() << endl;
        s << "last frame time  : " << ofGetLastFrameTime() << endl;
        s << "current scene id : " << mCurrentScene << endl;
//        s << "ez camera pos" << endl;
//        s << " x: " << mEzCam.getPosition().x << endl;
//        s << " y: " << mEzCam.getPosition().y << endl;
//        s << " z: " << mEzCam.getPosition().z << endl;
//        s << "camera pos" << endl;
//        s << " x: " << mCam.getPosition().x << endl;
//        s << " y: " << mCam.getPosition().y << endl;
//        s << " z: " << mCam.getPosition().z << endl;
        
        // info eace scenes
        
        ofColor col = ofGetBackground();
        ofSetColor(abs(255-col.r), abs(255-col.g), abs(255-col.b));
//        ofDrawBitmapString(s.str(), gui.getPosition().x, gui.getPosition().y + gui.getHeight()+20);
        ofDrawBitmapStringHighlight(s.str(), gui.getPosition().x, gui.getPosition().y + gui.getHeight()+20,
                                    ofColor(0, 64), ofColor(255));
        ofPopStyle();
        
        gui.draw();
    }
    
        // 図形から音に tmp
//        ofPushMatrix();
//        ofTranslate(20, 100);
//        ofSetColor(0, 255, 0);
//        ofNoFill();
//        ofBeginShape();
//        for (int i = 0; i < BUFFER_SIZE; i++)
//        {
//            ofVertex(i, mContoursWave[i] * 100);
//        }
//        ofEndShape(false);
//        ofPopMatrix();
//    }

}

//--------------------------------------------------------------
void AppCore::exit()
{
}

//--------------------------------------------------------------
void AppCore::keyPressed(int key)
{
    switch (key)
    {
        case OF_KEY_LEFT: changePreviousScene(); break;
        case OF_KEY_RIGHT: changeNextScene(); break;
        case OF_KEY_UP: mScenes[mCurrentScene]->setNextVariation(); break;
        case OF_KEY_DOWN: mScenes[mCurrentScene]->setPreviousVariation(); break;
            
        case 'f': ofToggleFullscreen(); break;
        case ' ': bDebugMode = !bDebugMode; break;
        case 'c': mScenes[mCurrentScene]->toggleManualCamera(); break;
//        case 'r': pd.sendBang("run"); break; ///<------------------------- Start Sound Track
//        case 's': pd.sendBang("stop"); break;///<------------------------- Stop Sound Track
            
        // send cue
        case '1': mScenes[mCurrentScene]->cue(1); break;
        case '2': mScenes[mCurrentScene]->cue(2); break;
        case '3': mScenes[mCurrentScene]->cue(3); break;
        case '4': mScenes[mCurrentScene]->cue(4); break;
        case '5': mScenes[mCurrentScene]->cue(5); break;
        case '0': mScenes[mCurrentScene]->cue(0); break;
            
        // TODO: konjoukei
        case 'q': pd.sendFloat("run_1", 1);break;
        case 'w': pd.sendFloat("run_2", 1);break;
        case 'e': pd.sendFloat("run_3", 1);break;
        case 'r': pd.sendFloat("run_4", 1);break;
        case 's': allSoundOff(); break;
        case 'b': toggleBlackOut(); break;
        case 'u': changeScene(1); break;
        case 'i': changeScene(3); break;
        case 'o': changeScene(4); break;
        case 'p': changeScene(5); break;
            
        // for debug
        case 'W':
            ofSetWindowPosition(0, 40);
            ofSetWindowShape(400, 400);
            break;
        case 'D':
            pd.sendBang("sound_debug");
            break;
            
            
        // 未定義のキー操作は各シーンクラスへ
        default: mScenes[mCurrentScene]->keyPressed(key); break;
    }
}

void AppCore::allSoundOff()
{
    pd.sendFloat("run_1", 0);
    pd.sendFloat("run_2", 0);
    pd.sendFloat("run_3", 0);
    pd.sendFloat("run_4", 0);
}

void AppCore::toggleBlackOut()
{
    bBlackOut = !bBlackOut;
}

//--------------------------------------------------------------
void AppCore::keyReleased(int key)
{
}

//--------------------------------------------------------------
void AppCore::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void AppCore::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void AppCore::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void AppCore::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void AppCore::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void AppCore::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void AppCore::dragEvent(ofDragInfo dragInfo)
{
}

//--------------------------------------------------------------
void AppCore::audioIn(float *input, int bufferSize, int nChannels)
{
#ifdef AUDIO_INPUT_TO_DRAW
    setAudioSamples(input, bufferSize, nChannels);
#endif
    pd.audioIn(input, bufferSize, nChannels);
}

void AppCore::audioOut(float *input, int bufferSize, int nChannels)
{
    pd.audioOut(input, bufferSize, nChannels);
#ifndef AUDIO_INPUT_TO_DRAW
    setAudioSamples(input, bufferSize, nChannels);
#endif
}

void AppCore::setAudioSamples(float *input, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++) {
        for (int j = 0; j < NUM_SAMPLES; j++) {
            mSamples[j][i] = input[i * nChannels + (j + INPUT_CH_OFFSET)];
        }
    }
}

//--------------------------------------------------------------
void AppCore::print(const std::string& message)
{
	cout << message << endl;
}

void AppCore::receiveBang(const std::string& dest)
{
}

void AppCore::receiveFloat(const std::string& dest, float value)
{
}

void AppCore::receiveSymbol(const std::string& dest, const std::string& symbol)
{
}

void AppCore::receiveList(const std::string& dest, const List& list)
{
}

void AppCore::receiveMessage(const std::string& dest, const std::string& msg, const List& list)
{
}

//--------------------------------------------------------------
void AppCore::receiveNoteOn(const int channel, const int pitch, const int velocity)
{
}

void AppCore::receiveControlChange(const int channel, const int controller, const int value)
{
}

// note: pgm nums are 1-128 to match pd
void AppCore::receiveProgramChange(const int channel, const int value)
{
}

void AppCore::receivePitchBend(const int channel, const int value)
{
}

void AppCore::receiveAftertouch(const int channel, const int value)
{
}

void AppCore::receivePolyAftertouch(const int channel, const int pitch, const int value)
{
}

// note: pd adds +2 to the port num, so sending to port 3 in pd to [midiout],
//       shows up at port 1 in ofxPd
void AppCore::receiveMidiByte(const int port, const int byte)
{
}



void AppCore::changeScene(const int scene)
{
    if (scene < mScenes.size()) {
        mCurrentScene = scene;
    }
    mScenes[mCurrentScene]->setup();
    bBlackOut = false;
    // fade
    
}

void AppCore::changeNextScene()
{
    mCurrentScene++;
    mCurrentScene %= mScenes.size();
    mScenes[mCurrentScene]->setup();
}

void AppCore::changePreviousScene()
{
    mCurrentScene--;
    if (mCurrentScene < 0) mCurrentScene = mScenes.size() - 1;
    mScenes[mCurrentScene]->setup();
}


void AppCore::fadeBackground(const ofColor &col)
{
    ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(col);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofDisableAlphaBlending();
    ofPopStyle();
}
