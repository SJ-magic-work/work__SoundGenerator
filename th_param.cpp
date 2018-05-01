/************************************************************
************************************************************/
#include "th_param.h"

/************************************************************
************************************************************/

/******************************
******************************/
THREAD_PARAM::THREAD_PARAM()
: Audio_Pan(0.5)
, Audio_Amp_max(0.5)
, Audio_Amp(Audio_Amp_max)
, Audio_Phase(0)
, WaveShape(WAVESHAPE_SIN)
, dt_Boot_toVolUp(5.0)
{
}

/******************************
******************************/
THREAD_PARAM::~THREAD_PARAM()
{
}

/******************************
******************************/
void THREAD_PARAM::threadedFunction()
{
	while(isThreadRunning()) {
		lock();
		
		unlock();
		
		
		sleep(1);
	}
}

/******************************
******************************/
void THREAD_PARAM::exit()
{
}

/******************************
******************************/
void THREAD_PARAM::setup()
{
	/********************
	********************/
	gui.setup();
	gui.add(Audio_Freq.setup("Audio_Freq", 50, 50, 10e3));
	gui.add(b_Mouse_VolControl.setup("b_Mouse_VolControl", false));
}

/******************************
******************************/
void THREAD_PARAM::update()
{
}

/******************************
******************************/
void THREAD_PARAM::draw()
{
	this->lock();
	gui.draw();
	this->unlock();
}

/******************************
******************************/
float THREAD_PARAM::get__dt_Boot_toVolUp()
{
	this->lock();
	float ret = dt_Boot_toVolUp;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_PARAM::get__Audio_Amp()
{
	this->lock();
	float ret = Audio_Amp;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_PARAM::get__Audio_Amp_max()
{
	this->lock();
	float ret = Audio_Amp_max;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_PARAM::get__Audio_Freq()
{
	this->lock();
	float ret = Audio_Freq;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
bool THREAD_PARAM::Is__Mouse_VolControl()
{
	this->lock();
	bool ret = b_Mouse_VolControl;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_PARAM::get__Audio_Phase()
{
	this->lock();
	float ret = Audio_Phase;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
void THREAD_PARAM::plus__Audio_Phase(float val)
{
	this->lock();
	Audio_Phase += val;
	while(TWO_PI < Audio_Phase){
		Audio_Phase -= TWO_PI;
	}
	this->unlock();
}

/******************************
******************************/
WAVESHAPE THREAD_PARAM::get__WaveShape()
{
	this->lock();
	WAVESHAPE ret = WaveShape;
	this->unlock();
	
	return ret;
}

/******************************
******************************/
void THREAD_PARAM::set__WaveShape(WAVESHAPE id)
{
	this->lock();
	if(int(id) < NUM_WAVESHAPES){
		WaveShape = id;
	}
	this->unlock();
}

/******************************
******************************/
void THREAD_PARAM::set__Audio_Amp(float val)
{
	this->lock();
	Audio_Amp = val;
	this->unlock();
}

/******************************
******************************/
void THREAD_PARAM::set__Graph_Raw_Audio(int id, float l_val, float r_val)
{
	this->lock();
	Graph_Raw_lAudio[id] = l_val;
	Graph_Raw_rAudio[id] = r_val;
	this->unlock();
}

/******************************
******************************/
float THREAD_PARAM::get__Graph_Raw_lAudio(int id)
{
	float ret;
	
	this->lock();
	ret = Graph_Raw_lAudio[id];
	this->unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_PARAM::get__Graph_Raw_rAudio(int id)
{
	float ret;
	
	this->lock();
	ret = Graph_Raw_rAudio[id];
	this->unlock();
	
	return ret;
}

