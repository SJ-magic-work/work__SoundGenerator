/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "stdio.h"

#include "ofMain.h"

/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

 enum{
	AUDIO_BUF_SIZE = 512,
	
	AUDIO_BUFFERS = 2,
	AUDIO_SAMPLERATE = 44100,
};

enum WAVESHAPE{
	WAVESHAPE_SIN,
	WAVESHAPE_SAWTOOTH,
	WAVESHAPE_RECT,
	WAVESHAPE_TRIANGLE,
	WAVESHAPE_WHITE_NOISE,
	
	NUM_WAVESHAPES,
};

enum{
	BUF_SIZE = 512,
};

/************************************************************
************************************************************/

/**************************************************
**************************************************/
class Noncopyable{
protected:
	Noncopyable() {}
	~Noncopyable() {}

private:
	void operator =(const Noncopyable& src);
	Noncopyable(const Noncopyable& src);
};

