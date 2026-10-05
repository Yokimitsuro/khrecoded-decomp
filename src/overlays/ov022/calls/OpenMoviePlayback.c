#include "nitro/types.h"

typedef struct MovieAudio {
    void *stream;
    s16 *leftBuffer;
    s16 *rightBuffer;
    u8 pad_0C[0x4];
    u32 sampleRate;
    u32 blockSize;
    u32 channels;
    s32 readIndex;
    u32 bufferBlocks;
} MovieAudio;

typedef struct MovieFrameTimer {
    void *stream;
    u8 alarm[0x2c];
    u8 pad_30[0x8];
    u8 frameReady;
    u8 paused;
    u8 active;
    u8 useMainScreen;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u64 frameTicks;
    void *(*getBuffer)(void);
} MovieFrameTimer;

typedef struct MovieGlobals {
    u8 stopped;
    u8 pad_01[3];
    MovieAudio *audio;
    MovieFrameTimer *mainTimer;
} MovieGlobals;

typedef struct MovieFileBank {
    u8 file[0x48];
    u8 pad_48[0xc];
    s32 option;
    BOOL stopping;
} MovieFileBank;

typedef struct MovieOpenParams {
    const char *path;
    s32 option;
    s32 useMainScreen;
} MovieOpenParams;

extern MovieFileBank data_ov022_020b7db4;
extern MovieGlobals data_ov022_020b7da8;
extern u8 sOv022_MobiclipIntr_020b7d30[];

extern void FS_InitFile(void *file);
extern void *Msg_BuildLangPath(const char *path);
extern void FS_OpenFile(void *file, void *path);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void SetupMovieDecoderArenas(void);
extern void *func_ov022_020a7d84(void);
extern void *func_ov022_020a7d9c(void);
extern void *createMovieStream(void *file, int slotCount);
extern u32 func_ov022_020a92c8(void *stream);
extern u32 func_ov022_020a92e0(void *stream);
extern u32 func_ov022_020a92f8(void *stream);
extern void DC_StoreAll(void);
extern void OS_InitAlarm(void);
extern void OS_CreateAlarm(void *alarm);
extern void func_ov022_020a9310(void *stream);
extern void func_ov022_020a809c(MovieFrameTimer *timer);
extern void flushPendingStereoAudioBlocks(MovieAudio *audio);
extern void FreeMovieFileBuffer(void);
extern void InvokeForChannelOrBoth(u32 mode, void *table, void *callback, int index);
extern void OS_WaitVBlankIntr(void);
extern void SwapCaptionPagesOnVBlank(void);

BOOL OpenMoviePlayback(const MovieOpenParams *params)
{
    MovieFileBank *bank = &data_ov022_020b7db4;
    MovieFrameTimer *timer;
    u32 channels;
    int i;
    MovieAudio *audio;

    bank->stopping = 0;
    FS_InitFile(bank);
    FS_OpenFile(bank, Msg_BuildLangPath(params->path));
    data_ov022_020b7da8.mainTimer = NNS_FndAllocFromDefaultExpHeapEx(sizeof(MovieFrameTimer), 0x20);
    MI_CpuFill8(data_ov022_020b7da8.mainTimer, 0, sizeof(MovieFrameTimer));
    timer = data_ov022_020b7da8.mainTimer;
    SetupMovieDecoderArenas();
    data_ov022_020b7db4.option = params->option;
    if (params->useMainScreen != 0) {
        data_ov022_020b7da8.mainTimer->getBuffer = func_ov022_020a7d84;
        data_ov022_020b7da8.mainTimer->useMainScreen = 1;
    } else {
        data_ov022_020b7da8.mainTimer->getBuffer = func_ov022_020a7d9c;
        data_ov022_020b7da8.mainTimer->useMainScreen = 0;
    }

    timer->stream = createMovieStream(bank, 10);
    if (timer->stream != NULL) {

    data_ov022_020b7da8.audio = NULL;
    channels = func_ov022_020a92f8(timer->stream);
    if (channels != 0) {
        data_ov022_020b7da8.audio = NNS_FndAllocFromDefaultExpHeapEx(sizeof(MovieAudio), 0x20);
        MI_CpuFill8(data_ov022_020b7da8.audio, 0, sizeof(MovieAudio));
        data_ov022_020b7da8.audio->stream = timer->stream;
        data_ov022_020b7da8.audio->channels = channels;
    }

    audio = data_ov022_020b7da8.audio;
    if (audio != NULL) {
        u64 period;
        u32 blocks;

        audio->sampleRate = func_ov022_020a92c8(audio->stream);
        period = 0xffb0ffULL / (0xffb0ffULL / audio->sampleRate);
        blocks = (u32)((period << 24) / ((u64)func_ov022_020a92e0(audio->stream) * audio->channels)) + 1;
        audio->blockSize = blocks;
        audio->bufferBlocks = blocks * 10;
        audio->leftBuffer = NNS_FndAllocFromDefaultExpHeapEx(audio->bufferBlocks * audio->channels * 2, 0x20);
        audio->rightBuffer = NNS_FndAllocFromDefaultExpHeapEx(audio->bufferBlocks * audio->channels * 2, 0x20);
        MI_CpuFill8(audio->leftBuffer, 0, audio->bufferBlocks * audio->channels * 2);
        MI_CpuFill8(audio->rightBuffer, 0, audio->bufferBlocks * audio->channels * 2);
        DC_StoreAll();
    }

    if (audio != NULL && audio->stream == timer->stream) {
        void *stream = audio->stream;
        u64 ticks = 0xffb0ffULL / audio->sampleRate;

        timer->frameTicks = ((u64)func_ov022_020a92e0(stream) * 0xffb0ffULL) / (ticks * audio->sampleRate);
        audio->readIndex = 0;
    } else {
        timer->frameTicks = func_ov022_020a92e0(timer->stream);
    }

    timer->paused = 0;
    timer->active = 1;
    OS_InitAlarm();
    OS_CreateAlarm(timer->alarm);
    timer->unk_44 = 0;
    timer->unk_40 = 0;
    timer->unk_48 = 0;
    timer->frameReady = 0;
    for (i = 0; i < 10; i++) {
        func_ov022_020a9310(timer->stream);
        func_ov022_020a809c(timer);
        if (audio != NULL && audio->stream == timer->stream) {
            flushPendingStereoAudioBlocks(audio);
        }
    }
    data_ov022_020b7da8.stopped = 0;
    InvokeForChannelOrBoth(1, sOv022_MobiclipIntr_020b7d30, SwapCaptionPagesOnVBlank, -1);
    OS_WaitVBlankIntr();
    return TRUE;
    }
    FreeMovieFileBuffer();
    NNSi_FndFreeFromDefaultHeap(timer);
    data_ov022_020b7da8.mainTimer = NULL;
    return FALSE;
}
