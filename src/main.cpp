#include "ofMain.h"
#include "ofApp.h"

int main( )
{
	ofGLFWWindowSettings settings;
	settings.setSize(1920, 1080);
	settings.setGLVersion(4, 5);
	settings.windowMode = OF_WINDOW;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
