#include "include/wave_player.h"


int main(int argc, char *argv[]) {
    char *filename = argv[1];
    WavePlayer wave_player(filename);
    wave_player.playWave();
    return 0;
}