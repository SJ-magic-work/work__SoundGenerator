/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class THREAD_PARAM : public ofThread, private Noncopyable{
private:
	/****************************************
	****************************************/
	/********************
	********************/
	ofxPanel gui;
	ofxFloatSlider Audio_Freq;
	ofxToggle b_Mouse_VolControl;
	
	/********************
	********************/
	float Graph_Raw_lAudio[AUDIO_BUF_SIZE];
	float Graph_Raw_rAudio[AUDIO_BUF_SIZE];
	
	float Audio_Pan;
	const float Audio_Amp_max;
	float Audio_Amp;
	float Audio_Phase;
	
	float dt_Boot_toVolUp;
	
	WAVESHAPE WaveShape;
	
	/****************************************
	function
	****************************************/
	/********************
	singleton
	********************/
	THREAD_PARAM();
	~THREAD_PARAM();
	THREAD_PARAM(const THREAD_PARAM&); // Copy constructor. no define.
	THREAD_PARAM& operator=(const THREAD_PARAM&); // コピー代入演算子. no define.
	
	/********************
	********************/
	void threadedFunction();
	
public:
	/****************************************
	****************************************/
	/********************
	********************/
	static THREAD_PARAM* getInstance(){
		static THREAD_PARAM inst;
		return &inst;
	}
	
	void exit();
	void setup();
	void update();
	void draw();
	
	
	float get__dt_Boot_toVolUp();
	float get__Audio_Amp();
	float get__Audio_Amp_max();
	float get__Audio_Freq();
	WAVESHAPE get__WaveShape();
	float get__Audio_Phase();
	float get__Graph_Raw_lAudio(int id);
	float get__Graph_Raw_rAudio(int id);
	
	bool Is__Mouse_VolControl();

	void set__Audio_Amp(float val);
	void set__WaveShape(WAVESHAPE id);
	void set__Graph_Raw_Audio(int id, float l_val, float r_val);
	
	void plus__Audio_Phase(float val);
};




