/**
 * Copyright (c) 2014 Tatsuya Ogusu
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 */
#include "testApp.h"

void testApp::setup()
{
    // the number if libpd ticks per buffer,
	// used to compute the audio buffer len: tpb * blocksize (always 64)
//	int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
    int ticksPerBuffer = BUFFER_SIZE / 64;
    
    int device = 0;
    if (!xml.loadFile("ini.xml"))
    {
        device = DEVICE_ID;
        xml.setValue("SOUND_DEVICE_ID", DEVICE_ID);
        xml.saveFile("ini.xml");
    }
    else
    {
        device = xml.getValue("SOUND_DEVICE_ID", DEVICE_ID);
    }

    ofSoundStreamListDevices();
    ss.setDeviceID(device);
    ss.setup(this, OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLE_RATE, ofxPd::blockSize()*ticksPerBuffer, 4);
    
    cout << "########## Audio Setup ##########" << endl;
    cout << "set audio device id: " << DEVICE_ID << endl;
    cout << "output channels: " << ss.getNumOutputChannels() << endl;
    cout << "input channels: " << ss.getNumInputChannels() << endl;
    cout << "sample rate: " << ss.getSampleRate() << endl;
    cout << "buffer size: " << ss.getBufferSize() << endl;
    cout << "tick count: " <<  ss.getTickCount() << endl;
    cout << "#################################" << endl;
    
    core.setup(OUTPUT_CHANNELS, INPUT_CHANNELS, SAMPLE_RATE, ticksPerBuffer);

}
void testApp::update(){ core.update(); }
void testApp::draw(){ core.draw(); }
void testApp::exit(){core.exit();}
void testApp::keyPressed(int key){core.keyPressed(key);}
void testApp::keyReleased(int key){core.keyReleased(key);}
void testApp::mouseMoved(int x, int y ){core.mouseMoved(x, y);}
void testApp::mouseDragged(int x, int y, int button){core.mouseDragged(x, y, button);}
void testApp::mousePressed(int x, int y, int button){core.mousePressed(x, y, button);}
void testApp::mouseReleased(int x, int y, int button){core.mouseReleased(x, y, button);}
void testApp::windowResized(int w, int h){core.windowResized(w, h);}
void testApp::gotMessage(ofMessage msg){core.gotMessage(msg);}
void testApp::dragEvent(ofDragInfo dragInfo){core.dragEvent(dragInfo);}
void testApp::audioIn(float *input, int bufferSize, int nChannels){core.audioIn(input, bufferSize, nChannels);}
void testApp::audioOut(float *input, int bufferSize, int nChannels){core.audioOut(input, bufferSize, nChannels);}
