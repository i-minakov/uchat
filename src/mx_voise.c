#include "../inc/header.h"

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS (15)
#define NUM_CHANNELS (2)

#define DITHER_FLAG (0) 
#define WRITE_TO_FILE (0)

#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE (0.0f)
#define PRINTF_S_FORMAT "%.8f"

typedef struct s_paTestData{
    int frameIndex;
    int maxFrameIndex;
    SAMPLE *recordedSamples;
}              t_paTestData;

static void mx_call_first(t_paTestData *data, long *framesToCalc, int *finished, unsigned long framesPerBuffer) {
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    if (framesLeft < framesPerBuffer) {
        *framesToCalc = framesLeft;
        *finished = paComplete;
    }
    else {
        *framesToCalc = framesPerBuffer;
        *finished = paContinue;
    }
}
static void mx_call_second(SAMPLE **wptr, long framesToCalc) {
    SAMPLE *s = *wptr;

    for (long i = 0; i < framesToCalc; i++) {
        *s++ = SAMPLE_SILENCE;
        if (NUM_CHANNELS == 2)
            *s++ = SAMPLE_SILENCE;
    }
}
static void mx_call_third(SAMPLE **wptr, const SAMPLE **rptr, long framesToCalc) {
    SAMPLE *s1 = *wptr;
    const SAMPLE *s2 = *rptr;

    for (long i = 0; i < framesToCalc; i++) {
        *s1++ = *s2++;
        if (NUM_CHANNELS == 2)
            *s1++ = *s2++;
    }
}
int mx_recordcallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData) {
    t_paTestData *data = (t_paTestData *)userData;
    const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    int finished;

    (void)outputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    (void)userData;
    mx_call_first(data, &framesToCalc, &finished, framesPerBuffer);
    if (inputBuffer == NULL)
        mx_call_second(&wptr, framesToCalc);
    else
        mx_call_third(&wptr, &rptr, framesToCalc);
    data->frameIndex += framesToCalc;
    return finished;
}

void mx_save_snd_file(t_paTestData data, int numSamples) { // change path
    SF_INFO sf_info;

    sf_info.channels = NUM_CHANNELS;
    sf_info.samplerate = SAMPLE_RATE;
    sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    const char *path = "./source/recorded.wav";
    SNDFILE *outfile = sf_open(path, SFM_WRITE, &sf_info);
    sf_count_t count = 0;

    count = sf_write_float(outfile, data.recordedSamples, numSamples);
    sf_write_sync(outfile);
    sf_close(outfile);
}

static void mx_close_voice(t_paTestData *data, PaError *err) {
    Pa_Terminate();
    if (data->recordedSamples)
        free(data->recordedSamples);
    if (*err != paNoError)
        *err = 1;
}
static void mx_enter_data(t_paTestData *data, PaError *err, int *numSamples) {
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
static void mx_enter_input(t_paTestData *data, PaError *err, PaStreamParameters *inputParameters) {
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
static void mx_voice_check(t_paTestData *data, PaError *err, PaStream *stream, t_main *m) {
    if (*err != paNoError)
        mx_close_voice(data, err);
    *err = Pa_StartStream(stream);
    if (*err != paNoError)
        mx_close_voice(data, err);
    for (int i = 0; i < 15 && (*err = Pa_IsStreamActive(stream)) == 1; i++) {
        if (m->micro_flag == 0)
            break;
        Pa_Sleep(1000);        
    }
    m->micro_flag = 0;
    if (*err < 0)
        mx_close_voice(data, err);
    *err = Pa_CloseStream(stream);
    if (*err != paNoError)
        mx_close_voice(data, err);
}

void mx_voice(t_main *m) {
    m->micro_flag = 1;
    PaStreamParameters inputParameters;
    PaStream *stream;
    PaError err = paNoError;
    t_paTestData data;
    int numSamples;

    mx_enter_data(&data, &err, &numSamples);
    mx_enter_input(&data, &err, &inputParameters);
    err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, mx_recordcallback, &data);
    mx_voice_check(&data, &err, stream, m);
    mx_save_snd_file(data, numSamples);
    mx_close_voice(&data, &err);
}

