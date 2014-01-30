/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#pragma once

#include "ofMain.h"
#include "ofxPd.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#include "Properties.h"
#include "BaseScene.h"
#include "SceneTest.h"
#include "SceneWave.h"
#include "SceneLissajous.h"
#include "SceneWhiteNote.h"
#include "SceneLissajousCube.h"
#include "SceneMatrix.h"

using namespace pd;

class AppCore : public pd::PdReceiver, public pd::PdMidiReceiver {
public:
    void setup(const int numOutChannels, const int numInChannels,
               const int sampleRate, const int ticksPerBuffer);
    void update();
    void draw();
    void exit();
    
    // input callbacks
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // audio callbacks
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut(float * input, int bufferSize, int nChannels);
    
    // pd message receiver callbacks
    void print(const std::string& message);
    void receiveBang(const std::string& dest);
    void receiveFloat(const std::string& dest, float value);
    void receiveSymbol(const std::string& dest, const std::string& symbol);
    void receiveList(const std::string& dest, const List& list);
    void receiveMessage(const std::string& dest, const std::string& msg, const pd::List& list);
    
    // pd midi receiver callbacks
    void receiveNoteOn(const int channel, const int pitch, const int velocity);
    void receiveControlChange(const int channel, const int controller, const int value);
    void receiveProgramChange(const int channel, const int value);
    void receivePitchBend(const int channel, const int value);
    void receiveAftertouch(const int channel, const int value);
    void receivePolyAftertouch(const int channel, const int pitch, const int value);
    void receiveMidiByte(const int port, const int byte);

private:
    
    void setAudioSamples(float * input, int bufferSize, int nChannels);
    void changeScene(const int scene);
    void changeNextScene();
    void changePreviousScene();
    void fadeBackground(const ofColor& col);
    
    // ================== 根性系
    void allSoundOff();
    void toggleBlackOut();
    
    bool bBlackOut;
    
    // scenes
    vector<BaseScene *> mScenes;
    int mCurrentScene;
    
    // mode and flag
    bool bDebugMode;
    
    /**
     *  Samples.
     * ２重配列 [入力ch数][バッファサイズ]
     */
    float mSamples[NUM_SAMPLES][BUFFER_SIZE];
    
    vector<float> mContoursWave;
    
    ofxFloatSlider mMasterVolume;
    ofxPanel gui;
    
    ofxPd pd;
    
};
