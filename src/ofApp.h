#pragma once

#include "ofMain.h"
#include "ShaderObject.h"
#include "SoundAnalyzer.h"
#include "MusicPlayer.h"

class ofApp : public ofBaseApp 
{

    public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);

    private:
        ShaderObject shader;
        SoundAnalyzer analyzer;
        MusicPlayer musicPlayer;
};
