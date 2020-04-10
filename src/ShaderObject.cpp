#include "ShaderObject.h"

void ShaderObject::setup(string shaderPath) 
{
	shader.load(shaderPath);
}

void ShaderObject::update(const vector<float>& vols, const vector<bool>& beats,
		float centroid, float time) 
{
	this->vols = vols;
	this->beats = beats;
	centr = ofMap(centroid, 0, 10000, 0.0, 1.0);
	this->time = time;
}

void ShaderObject::draw() 
{
	ofPushMatrix();
	shader.begin();
		setTransforms();
		setUniforms();
		ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
	shader.end();
	ofPopMatrix();
}

void ShaderObject::setUniforms() 
{
	shader.setUniform1f("centr", centr);
	shader.setUniform1f("bass", vols[0]);
	shader.setUniform1f("mids", vols[1]);
	shader.setUniform1f("high", vols[2]);
	shader.setUniform1i("beat", (int)beats[0]);
	shader.setUniform1f("u_time", time/1000.0);
	shader.setUniform2i("u_resolution", ofGetWidth(), ofGetHeight());
}

void ShaderObject::setTransforms() 
{
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
}
