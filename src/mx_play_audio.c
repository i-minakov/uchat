#include "../inc/header.h"

static void cost_vars(const void *input,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags) {
    (void)input;
    (void)timeInfo;
    (void)statusFlags;
}

static int callback(const void *input,
                    void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
    float           *out;
    t_callback_data_s *p_data = (t_callback_data_s*)userData;
    sf_count_t       num_read;

    out = (float*)output;
    p_data = (t_callback_data_s*)userData;
    memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);
    num_read = sf_read_float(p_data->file, out,
                             frameCount * p_data->info.channels);
    if ((unsigned long) num_read < frameCount) {
        return paComplete;
    }
    cost_vars(input, timeInfo, statusFlags);
    return paContinue;
}

void mx_play_audio(char *path) {
    PaStream *stream;
    PaError error;
    t_callback_data_s data;

    data.file = sf_open(path, SFM_READ, &data.info);
    error = Pa_Initialize();
    error = Pa_OpenDefaultStream(&stream
                                 ,0 /* no input */
                                 ,data.info.channels /* stereo out */
                                 ,paFloat32 /* floating point */
                                 ,data.info.samplerate
                                 ,FRAMES_PER_BUFFER
                                 ,callback
                                 ,&data); /* our sndfile data struct */
    error = Pa_StartStream(stream);
    while (Pa_IsStreamActive(stream))
        Pa_Sleep(100);
    sf_close(data.file);
    error = Pa_CloseStream(stream);
    error = Pa_Terminate();
    g_idle_remove_by_data(path);
}
