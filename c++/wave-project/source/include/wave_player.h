#ifndef WAVE_PLAYER_H_
#define WAVE_PLAYER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mixer.h>

#include "wave_decoder.h"


class WavePlayer {
private :
    WaveDecoder wave_decoder;
    WaveDecoder::WaveInfo wInfo;

    SDL_Window *window;
    SDL_Surface *screen, *image, *image_loading;
    Mix_Chunk sound;
    SDL_Event event;
    SDL_Rect src, dest;

    void showLoadingScreen();
    void showMenuScreen();

    void initializeVideoAndAudio();
    void initializeWindowAndScreens();

public:
    WavePlayer(const char *filename);

    void playWave();
    void changeSampleRate(uint32_t new_rate);
};

#endif