#include "ofApp.h"

void ofApp::setup() 
{
    float audioVolume = 0.5;
    float smoothing = 0.9;
    string songPath = "music/haveadream.ogg";

    vector<int> lims { 10,18,40 };
    vector<float> adjs { 0.254, 0.142, 0.037 };
    // 	lims.push_back(8);
    // 	lims.push_back(40);
    // 	lims.push_back(240);

    musicPlayer.load(songPath, audioVolume);
    analyzer.setup(audioVolume, smoothing, lims, adjs);
    shader.setup("shaders/shader");

    ofBackground(ofColor::black);
}

void ofApp::update() 
{
    // Do the FFT analysis and update variables
    analyzer.analyze(); 

    // Send the variables to shader
    shader.update(analyzer.getVols(), analyzer.getBeats(),
            analyzer.getCentroid(), musicPlayer.getTime());
}

void ofApp::draw() 
{
    shader.draw();
}

void ofApp::keyPressed(int key) 
{
    musicPlayer.keyPressed(key);
}
