#include "nitro/types.h"

typedef struct {
    void *open;
    void *step;
    void *render;
    void *setMode;
    void *isOpen;
    void *close;
    void *start;
    void *isRunning;
    void *stopAudio;
    void *reserved;
    void *isPaused;
} MovieCallbacks;

extern void func_ov032_020bb468(int arg);
extern void func_ov032_020bb480(void);
extern void func_ov032_020bb49c(void);
extern void SetContextModeAndFlag(u8 mode);
extern BOOL MobiClip_SrcIsOpen(void);
extern void MobiClip_SrcClose(void);
extern void StartMoviePlayback(void *params);
extern BOOL IsContextFlag10Clear(void);
extern void func_ov032_020bb388(s32 keepAlive);
extern u32 IsContextFlag20Set(void);
extern int func_ov001_020645c8(int flag);
extern void ApplyAreaMusicEntry(int entry);

void InstallMovieCallbacks(MovieCallbacks *callbacks)
{
    callbacks->open = func_ov032_020bb468;
    callbacks->step = func_ov032_020bb480;
    callbacks->render = func_ov032_020bb49c;
    callbacks->setMode = SetContextModeAndFlag;
    callbacks->isOpen = MobiClip_SrcIsOpen;
    callbacks->close = MobiClip_SrcClose;
    callbacks->start = StartMoviePlayback;
    callbacks->isRunning = IsContextFlag10Clear;
    callbacks->stopAudio = func_ov032_020bb388;
    callbacks->isPaused = IsContextFlag20Set;
    ApplyAreaMusicEntry(func_ov001_020645c8(0x3ee4) ? 4 : 0);
}
