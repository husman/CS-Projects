#include "include/wave_player.h"


WavePlayer::WavePlayer(const char *filename) {
    if(wave_decoder.decodeWave(filename, &wInfo) == -1) {
        printf("Failed to decode input file.\n");
        exit(-1);
    }
}

void WavePlayer::changeSampleRate(uint32_t new_rate) {
    wInfo.dwSamplesPerSec = new_rate;
    wInfo.dwAvgBytesPerSec = wInfo.dwSamplesPerSec * wInfo.wChannels * wInfo.wBitsPerSample / 8;
}

void WavePlayer::showLoadingScreen() {
    SDL_BlitSurface(image_loading, &src, screen, &dest);
    SDL_UpdateWindowSurface(window);
}

void WavePlayer::showMenuScreen() {
    SDL_Delay(1000);
    SDL_BlitSurface(image, &src, screen, &dest);
    SDL_UpdateWindowSurface(window);
}

void WavePlayer::initializeVideoAndAudio() {
    //Initialize BOTH SDL video and SDL audio
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return;
    }

    Uint16 audio_format;
    audio_format = wInfo.wBitsPerSample == 8? (uint16_t) AUDIO_S8 : (uint16_t) AUDIO_S16SYS;

    //Initialize SDL_mixer with our chosen audio settings
    if(Mix_OpenAudio(wInfo.dwSamplesPerSec, audio_format, wInfo.wChannels, wInfo.data_chunk_size) != 0) {
        printf("Unable to initialize audio: %s\n", Mix_GetError());
        exit(1);
    }

    sound.abuf = (uint8_t *)wInfo.data;
    sound.alen = wInfo.data_chunk_size;
    sound.allocated = 1;
    sound.volume = 128;
}

void WavePlayer::initializeWindowAndScreens() {
    //Set the video mode to anything, just need a window
    window = SDL_CreateWindow(
            "Wave Audio Player",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            531, 431, 0
    );
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return;
    }

    image = SDL_LoadBMP("images/Einstein.bmp");
    if (image == NULL) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return;
    }

    image_loading = SDL_LoadBMP("images/loading.bmp");
    if (image_loading == NULL) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return;
    }

    src.x = 0;
    src.y = 0;
    src.w = image->w;
    src.h = image->h;

    dest.x = 0;
    dest.y = 0;
    dest.w = image->w;
    dest.h = image->h;
}

void WavePlayer::playWave() {
    int channel;
    int quit;
    int audio_rate_orignal = wInfo.dwSamplesPerSec;

    initializeVideoAndAudio();
    initializeWindowAndScreens();
    showMenuScreen();

    //Play our sound file, and capture the channel on which it is played
    channel = Mix_PlayChannel(-1, &sound, 0);
    if(channel == -1) {
        printf("Unable to play WAV file: %s\n", Mix_GetError());
    }
    printf("Starting audio playback. See the pop-up window...\n");

    /* Enable Unicode translation */
    quit = 0;
    /* Loop until an SDL_QUIT event is found */
    while( !quit ){

        /* Poll for events */
        while(SDL_PollEvent(&event)){

            switch(event.type){
                /* Keyboard event */
                /* Pass the event data onto PrintKeyInfo() */
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        showLoadingScreen();
                        printf("[Command - Esc] Stopping audio playback and exiting...\n");
                        quit = 1;
                        break;
                    case SDLK_r: // Restart
                        showLoadingScreen();
                        printf("[Command - R] Restarting audio playback...\n");
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        showMenuScreen();
                        break;
                    case SDLK_s: // Stop
                        showLoadingScreen();
                        printf("[Command - S] Pauing audio playback...\n");
                        Mix_Pause(channel);
                        showMenuScreen();
                        break;
                    case SDLK_p: // Play
                        showLoadingScreen();
                        if(Mix_Playing(channel) != 0) {
                            printf("[Command - P] Resuming audio playback from previous point...\n");
                            Mix_Resume(channel);
                        } else {
                            printf("[Command - P] Resuming audio playback from beginning...\n");
                            channel = Mix_PlayChannel(channel, &sound, 0);
                        }
                        showMenuScreen();
                        break;
                    case SDLK_1: // Original
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(audio_rate_orignal);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 1] Sample rate changed to %u Hz (Original)...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_2: // 8kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(8000);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 2] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_3: // 11kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(16000);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 3] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_4: // 11kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(22050);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 4] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_5: // 32kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(32000);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 5] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_6: // 44kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(44056);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 6] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_7: // 88kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(88200);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 7] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_8: // 96kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(96000);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 8] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_9: // 176kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(176400);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 9] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    case SDLK_0: // 192kHz
                        showLoadingScreen();
                        Mix_CloseAudio();
                        changeSampleRate(192000);

                        //Let's play back at new rate
                        initializeVideoAndAudio();
                        channel = Mix_PlayChannel(channel, &sound, 0);
                        printf("[Command - 0] Sample rate changed to %u Hz...\n", wInfo.dwSamplesPerSec);
                        showMenuScreen();
                        break;
                    }
                    break;
                // SDL_QUIT event (window close)
                case SDL_QUIT:
                    showLoadingScreen();
                    printf("[Command - quit] Stopping audio playback and exiting...\n");
                    quit = 1;
                    break;
                default:
                    break;
            }
        }
    }

    // Release resources held by our images
    SDL_FreeSurface(image_loading);
    SDL_FreeSurface(image);

    //Need to make sure that SDL_mixer and SDL have a chance to clean up
    Mix_CloseAudio();
    SDL_Quit();

    printf("\naudio playback complete\n\n");
}