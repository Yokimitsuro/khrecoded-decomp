#include "nitro/types.h"

typedef struct MovieAudio {
    void *stream;
    s16 *leftBuffer;
    s16 *rightBuffer;
} MovieAudio;

typedef struct MovieFrameTimer {
    void *stream;
    u8 alarm[0x2c];
} MovieFrameTimer;

typedef struct MovieGlobals {
    u8 stopped;
    u8 pad_01[3];
    MovieAudio *audio;
    MovieFrameTimer *mainTimer;
} MovieGlobals;

typedef struct MovieFileBank {
    u8 file[0x48];
    u8 pad_48[0x10];
    BOOL stopping;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7db4;
extern MovieGlobals data_ov022_020b7da8;
extern u8 sOv022_MobiclipIntr_020b7d30[];

extern int runMovieSlotState(MovieFrameTimer *timer);
extern void OS_CancelAlarm(void *alarm);
extern void OS_EndAlarm(void);
extern void NotifyBothOrOne(u32 mode, u32 table, int index);
extern void StopMovieAudio(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov022_020a92a8(void *stream);
extern BOOL FS_CloseFile(void *file);
extern void FreeMovieFileBuffer(void);

void StopMoviePlayback(void)
{
    MovieFileBank *bank = &data_ov022_020b7db4;
    MovieFrameTimer *timer = data_ov022_020b7da8.mainTimer;
    MovieAudio *audio = data_ov022_020b7da8.audio;

    if (bank->stopping == 0) {
        bank->stopping = 1;
        while (runMovieSlotState(timer) != 0) {
        }
    }
    OS_CancelAlarm(timer->alarm);
    OS_EndAlarm();
    NotifyBothOrOne(1, (u32)sOv022_MobiclipIntr_020b7d30, -1);
    if (audio != NULL) {
        StopMovieAudio();
        NNSi_FndFreeFromDefaultHeap(audio->leftBuffer);
        NNSi_FndFreeFromDefaultHeap(audio->rightBuffer);
        NNSi_FndFreeFromDefaultHeap(audio);
        data_ov022_020b7da8.audio = NULL;
    }
    func_ov022_020a92a8(timer->stream);
    FS_CloseFile(bank->file);
    NNSi_FndFreeFromDefaultHeap(data_ov022_020b7da8.mainTimer);
    data_ov022_020b7da8.mainTimer = NULL;
    FreeMovieFileBuffer();
}
