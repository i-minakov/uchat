#include "../../inc/header.h"

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

void mx_save_snd_file(t_paTestData data, int numSamples, char *name) {
    SF_INFO sf_info;

    sf_info.channels = NUM_CHANNELS;
    sf_info.samplerate = SAMPLE_RATE;
    sf_info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    char *path = mx_super_join("./source/cash_", name, 0);

    path = mx_super_join(path, ".wav", 1);
    remove(path);
    SNDFILE *outfile = sf_open(path, SFM_WRITE, &sf_info);
    sf_count_t count = 0;

    count = sf_write_float(outfile, data.recordedSamples, numSamples);
    sf_write_sync(outfile);
    sf_close(outfile);
}
