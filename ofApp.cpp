/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _soundStream_Output_DeviceId)
: soundStream_Output_DeviceId(_soundStream_Output_DeviceId)
, th_Param(THREAD_PARAM::getInstance())
, fp_Log_main(NULL)
, fp_Log_AudioInOut(NULL)
, d_LogProcessTime(10.0)
{
	fp_Log_main = fopen("../../../data/Log_main.csv", "w");
	fp_Log_AudioInOut = fopen("../../../data/Log_Audio.csv", "w");
}

/******************************
******************************/
ofApp::~ofApp()
{
	if(fp_Log_main) fclose(fp_Log_main);
	if(fp_Log_AudioInOut) fclose(fp_Log_AudioInOut);
}

/******************************
******************************/
void ofApp::exit()
{
	th_Param->exit();
	printf("Good-bye\n");
}


//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("Sound Generator");
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	/********************
	********************/
	th_Param->setup();

	/********************
	********************/
	soundStream.listDevices();
	if( soundStream_Output_DeviceId == -1 ){
		ofExit();
		return;
	}
	// soundStream.setDeviceID(soundStream_DeviceId);
	/* set in & out respectively. */
	// soundStream.setInDeviceID(soundStream_Input_DeviceId);  
	soundStream.setOutDeviceID(soundStream_Output_DeviceId);
	
	/********************
	********************/
	soundStream.setup(this, 2/* out */, 0/* in */, AUDIO_SAMPLERATE, AUDIO_BUF_SIZE, AUDIO_BUFFERS);
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	float now = ofGetElapsedTimef();
	if(now < d_LogProcessTime) fprintf(fp_Log_main, "%f,", now);
	
	/********************
	********************/
	if(th_Param->Is__Mouse_VolControl()){
		th_Param->set__Audio_Amp(ofMap(mouseY, ofGetHeight(), 0, 0, th_Param->get__Audio_Amp_max(), true));
	}else{
		th_Param->set__Audio_Amp(th_Param->get__Audio_Amp_max());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	ofBackground(20);

	/********************
	********************/
	float audioHeight = ofGetHeight() / 4.0f;
	float phaseDiff = ofGetWidth() / float(AUDIO_BUF_SIZE);
	
	/********************
	********************/
	ofSetColor(0, 0, 255);
	ofNoFill();
	ofSetLineWidth(2);
	
	ofPushMatrix();
	ofTranslate(0, audioHeight);
	ofScale(1, -1, 1);
		ofBeginShape();
		for(int i = 0; i < AUDIO_BUF_SIZE; i++){
			ofVertex(i * phaseDiff, th_Param->get__Graph_Raw_lAudio(i) * audioHeight);
		}
		ofEndShape();
	ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate(0, audioHeight * 3);
	ofScale(1, -1, 1);
		ofBeginShape();
		for(int i = 0; i < AUDIO_BUF_SIZE; i++){
			ofVertex(i * phaseDiff, th_Param->get__Graph_Raw_rAudio(i) * audioHeight);
		}
		ofEndShape();
	ofPopMatrix();
	
	/********************
	********************/
	th_Param->draw();
	
	/********************
	********************/
	{
		float now = ofGetElapsedTimef();
		if(now < d_LogProcessTime) fprintf(fp_Log_main, "%f\n", now);
	}
}

/******************************
audioIn/ audioOut
	同じthreadで動いている様子。
	また、audioInとaudioOutは、同時に呼ばれることはない(多分)。
	つまり、ofAppからaccessがない限り、変数にaccessする際にlock/unlock する必要はない。
	ofApp側からaccessする時は、threadを立てて、安全にpassする仕組みが必要
******************************/
void ofApp::audioIn(float *input, int bufferSize, int nChannels)
{
}  

/******************************
******************************/
void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
	/********************
	********************/
	float now = ofGetElapsedTimef();
	if(now < d_LogProcessTime) fprintf(fp_Log_AudioInOut, "%f,", now);
	
	/********************
	********************/
	float _AudioAmp;
	if(now < th_Param->get__dt_Boot_toVolUp()){
		_AudioAmp = th_Param->get__Audio_Amp() / th_Param->get__dt_Boot_toVolUp() * now;
	}else{
		_AudioAmp = th_Param->get__Audio_Amp();
	}
 	
	/********************
	********************/
	float sample;
	float phaseDiff;
	
	phaseDiff = TWO_PI * th_Param->get__Audio_Freq() / AUDIO_SAMPLERATE;
	
	for(int i = 0; i < bufferSize; i++){
		th_Param->plus__Audio_Phase(phaseDiff);
		
		switch(th_Param->get__WaveShape()){
			case WAVESHAPE_SIN:
				sample = sin(th_Param->get__Audio_Phase());
				break;
				
			case WAVESHAPE_SAWTOOTH:
				sample = -th_Param->get__Audio_Phase() / PI + 1;
				break;
				
			case WAVESHAPE_RECT:
				sample = (th_Param->get__Audio_Phase() < PI) ? -1 : 1;
				break;
				
			case WAVESHAPE_TRIANGLE:
				sample = (th_Param->get__Audio_Phase() < PI) ? -2 / PI * th_Param->get__Audio_Phase() + 1 : 2 / PI * th_Param->get__Audio_Phase() - 3;
				break;
				
			case WAVESHAPE_WHITE_NOISE:
				sample = ofRandom(-1, 1);
				break;
		}
		
		output[i * nChannels + 0] = sample * _AudioAmp;
		output[i * nChannels + 1] = sample * _AudioAmp;
		th_Param->set__Graph_Raw_Audio(i, output[i * nChannels + 0], output[i * nChannels + 1]);
	}
	
	/********************
	********************/
	if(now < d_LogProcessTime) fprintf(fp_Log_AudioInOut, "%f\n", ofGetElapsedTimef());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			int id = key - '0';
			th_Param->set__WaveShape(WAVESHAPE(id));
		}
			break;
			
		case ' ':
		{
			char buf[BUF_SIZE];
			
			sprintf(buf, "image.png");
			ofSaveScreen(buf);
			printf("> %s saved\n", buf);
		}
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
