#ifndef AUDIO_HEDER_H
#define AUDIO_HEDER_H

#define FRAMES_PER_BUFFER (512)

#include "../source/libportaudio/include/portaudio.h"
#include "../source/libsndfile/include/sndfile.h"

typedef struct s_callback_data_s{
    SNDFILE     *file;
    SF_INFO      info;
}              t_callback_data_s;

void mx_play_audio(char *path);

#endif
