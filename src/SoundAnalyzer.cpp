#include "SoundAnalyzer.h"

void SoundAnalyzer::setup(float volume, float smoothing, const vector<int>& lims) 
{
	adjustments.assign(lims.size(), 1.0);
	setup(volume, smoothing, lims, adjustments);
}

void SoundAnalyzer::setup(float volume, float smoothing, const vector<int>& lims, const vector<float>& adjustments) 
{ 
	audioVolume = volume;
	this->smoothing = smoothing;
	this->lims = lims;
	this->adjustments = adjustments;
	previousSpectrum.fill(0.0);

	int nRanges = lims.size();
	meanVolumes.resize(nRanges);
	setupBeatDetection(nRanges);
}

void SoundAnalyzer::setupBeatDetection(int nRanges) 
{
	beatDetections.resize(nRanges);
	decayRates.assign(nRanges, 0.05);
	decayRates[1] = 0.03;
	minimumThresholds.assign(nRanges, 0.1);
	thresholds.assign(nRanges, 0.1); //should be same as min thresholds
}

void SoundAnalyzer::analyze() 
{
	ofSoundUpdate();
	spectrum = ofSoundGetSpectrum(FFTBANDS);

	// Smoothing
	for (int i = 0; i < FFTBANDS; ++i) 
    {
		spectrum[i] = ofLerp(spectrum[i], previousSpectrum[i], smoothing);
		previousSpectrum[i] = spectrum[i];
	}

	// Get means (which might be very small) and normalize (needs to be set)
	int lastLim = 0;
	for (size_t i = 0; i < lims.size(); ++i) 
    {
		meanVolumes[i] = getMeanValue(spectrum, lastLim, lims[i]) / audioVolume;
		meanVolumes[i] = ofMap(meanVolumes[i], 0, adjustments[i], 0.0, 1.0, true);
		lastLim = lims[i];
	}
	
	// Centroid
	centroid = calculateCentroid(spectrum);

	// Onset detection
	detectBeats();
}

float SoundAnalyzer::getMeanValue(float * vals, int startIndex, int endIndex) 
{
	float meanValue = 0;
	for (int i = startIndex; i < endIndex; ++i) 
    {
		meanValue += vals[i];
	}
	return meanValue /= (endIndex - startIndex);
}

void SoundAnalyzer::detectBeats() 
{
	// Onset detection for all the ranges being analyzed
	for (size_t i = 0; i < beatDetections.size(); ++i) 
    {
		thresholds[i] = ofLerp(thresholds[i], minimumThresholds[i], decayRates[i]);

		if (meanVolumes[i] > 1.2 * thresholds[i]) 
        {
			thresholds[i] = meanVolumes[0];
			beatDetections[i] = true;
		} 
        else if (meanVolumes[i] > thresholds[i]) 
        {
		// if ( meanVolumes[i] > thresholds[i] && meanVolumes[i] > 0.5) {
			thresholds[i] = meanVolumes[i];
			beatDetections[i] = true;
		} 
        else 
        {
			beatDetections[i] = false;
		}
	}
}

int SoundAnalyzer::calculateCentroid(float* vals) 
{
	float cumulativeSum = 0;
	float centroidNormalization = 0;
	float nyquistFrequency = 22050; //assuming sample rate of 44100

	for (int i = 0; i < FFTBANDS; ++i) 
    {
		cumulativeSum += i * vals[i];
		centroidNormalization += vals[i];
	}

	int indexOfMeanFrequency = 0;

	if (centroidNormalization) 
    {
		indexOfMeanFrequency = (int)(cumulativeSum / centroidNormalization);
	}

	float centroidFrequency = indexOfMeanFrequency * (nyquistFrequency / FFTBANDS);
	return centroidFrequency > 10000 ? 1 : centroidFrequency; //otherwise gigantic when volume is low 
}
