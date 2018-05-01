#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	/********************
	********************/
	int soundStream_Output_DeviceId;

	/********************
	********************/
	if(argc < 2){
		/********************
		********************/
		printf("> exe AudioOutput\n");
		
		/********************
		********************/
		soundStream_Output_DeviceId = -1;
		
		ofRunApp(new ofApp(soundStream_Output_DeviceId));
		
	}else{
		/********************
		********************/
		soundStream_Output_DeviceId = atoi(argv[1]);
		
		ofRunApp(new ofApp(soundStream_Output_DeviceId));
	}
}
