#pragma once

#include "ofMain.h"

class ShaderObject 
{
    public:
        void setup(string shaderPath);
        void update(const vector<float>& vols, const vector<bool>& beats, float
                centroid, float time);
        void draw();
        void setUniforms();
        void setTransforms();

    private:
        ofShader shader;
        float centr;
        vector<float> vols;
        vector<bool> beats;
        float time;
};
