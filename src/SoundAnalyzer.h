#pragma once

#include "ofMain.h"
#define FFTBANDS 512

class SoundAnalyzer {


	public:
        void setup(float volume, float smoothing, const vector<int>& lims);
        void setup(float volume, float smoothing, const vector<int>& lims, const
                vector<float>& adjustments);
		void analyze();

		vector<float> getVols() {return meanVolumes; }
		vector<bool> getBeats() { return beatDetections; }
		float getCentroid() { return centroid; }

	private:
        float getMeanValue(float * vals, int startIndex, int endIndex);
		void setupBeatDetection(int nRanges);
		void detectBeats();
		int calculateCentroid(float* vals);

		float * spectrum;

		// Smoothing
		std::array<float, FFTBANDS> previousSpectrum;
		float smoothing;
		float audioVolume;

		// Decides which bin the freqency range should end by
		vector<int> lims;

		// Adjusting for low peak volume (different for each range)
		vector<float> adjustments;

		// Sound analysis results (can be got with the get- functions)
		vector<float> meanVolumes;
		vector<bool> beatDetections;
		float centroid;

        // onset detection (settings can be adjusted for the different ranges)
		vector<float> thresholds;
		vector<float> minimumThresholds;
		vector<float> decayRates;
};
