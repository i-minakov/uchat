#include "../../inc/header.h"

static void mx_close_voice(t_paTestData *data, PaError *err) {
    Pa_Terminate();
    if (data->recordedSamples)
        free(data->recordedSamples);
    if (*err != paNoError)
        *err = 1;
}

static void mx_enter_data(t_paTestData *data,
                          PaError *err, int *numSamples) {
    int totalFrames;
    int numBytes;

    data->maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE;
    data->frameIndex = 0;
    *numSamples = totalFrames * NUM_CHANNELS;
    numBytes = *numSamples * sizeof(SAMPLE);
    data->recordedSamples = (SAMPLE *)malloc(numBytes);
    if (data->recordedSamples == NULL)
        mx_close_voice(data, err);
    for (int i = 0; i < *numSamples; i++)
        data->recordedSamples[i] = 0;
}

static void mx_enter_input(t_paTestData *data, PaError *err,
                           PaStreamParameters *inputParameters) {
    *err = Pa_Initialize();
    if (*err != paNoError)
        mx_close_voice(data, err);
    inputParameters->device = Pa_GetDefaultInputDevice();
    if (inputParameters->device == paNoDevice)
        mx_close_voice(data, err);
    inputParameters->channelCount = 2;
    inputParameters->sampleFormat = PA_SAMPLE_TYPE;
    inputParameters->suggestedLatency = Pa_GetDeviceInfo(inputParameters->device)->defaultLowInputLatency;
    inputParameters->hostApiSpecificStreamInfo = NULL;
}

static void mx_voice_check(t_paTestData *data,
                           PaError *err, PaStream *stream) {
    if (*err != paNoError)
        mx_close_voice(data, err);
    *err = Pa_StartStream(stream);
    if (*err != paNoError)
        mx_close_voice(data, err);
    while ((*err = Pa_IsStreamActive(stream)) == 1)
        Pa_Sleep(1000);
    if (*err < 0)
        mx_close_voice(data, err);
    *err = Pa_CloseStream(stream);
    if (*err != paNoError)
        mx_close_voice(data, err);
}

void mx_voice_save(char *path, t_main *m) {
    PaStreamParameters inputParameters;
    PaStream *stream;
    PaError err = paNoError;
    t_paTestData data;
    int numSamples;
    t_add_m *s = create_struct("recodered.wav", true, 0, NULL);

    mx_enter_data(&data, &err, &numSamples);
    mx_enter_input(&data, &err, &inputParameters);
    err = Pa_OpenStream(&stream, &inputParameters, NULL,
        SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, mx_recordcallback, &data);
    mx_voice_check(&data, &err, stream);
    mx_save_snd_file(data, numSamples, path);
    mx_close_voice(&data, &err);
    add_file(mx_activ_us(m), s, 1, mx_activ_us(m)->exist_id ? 
            mx_atoi(mx_activ_us(m)->exist_id->data) + 1 : 1);
    command_msg(mx_activ_us(m), s, 1);
    free(s);
}

