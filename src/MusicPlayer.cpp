#include "MusicPlayer.h"

void MusicPlayer::load(string songPath, float audioVolume) 
{
	player.load(songPath);
	player.setVolume(audioVolume);
	player.play();
	player.setPaused(true);
}

void MusicPlayer::keyPressed(int key) 
{
    int playhead = player.getPositionMS();

	switch (key) {
        // Pause
		case ' ': 
			player.setPaused(player.isPlaying());
			break;
        // Jump forward
		case OF_KEY_RIGHT:
			player.setPositionMS(playhead + 15000);
			break; 
        // Jump backward
		case OF_KEY_LEFT:
			player.setPositionMS(playhead - 15000);
			break; 
        // Stop playback
		case 's':
			player.stop();
			break;
        // Go fullscreen
		case 'f':
			ofToggleFullscreen();
			break;
	}
}

float MusicPlayer::getTime() 
{
	return player.getPositionMS();
}
