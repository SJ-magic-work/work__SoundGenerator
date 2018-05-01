/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

#include "th_param.h"

/************************************************************
************************************************************/

class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WINDOW_WIDTH = 1200,
		WINDOW_HEIGHT = 900,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	FILE* fp_Log_main;
	FILE* fp_Log_AudioInOut;
	
	const float d_LogProcessTime;
	
	/********************
	********************/
	int soundStream_Output_DeviceId;
	ofSoundStream soundStream;
	
	THREAD_PARAM* th_Param;
	
	/****************************************
	****************************************/
	void audioIn(float *input, int bufferSize, int nChannels);
	void audioOut(float *output, int bufferSize, int nChannels);
	
	
public:
	/****************************************
	****************************************/
	ofApp(int _soundStream_Output_DeviceId);
	~ofApp();
	
	void exit();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
