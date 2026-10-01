typedef unsigned int u32;

typedef struct NNSSndStrm {
    unsigned char link[8];
    unsigned char preSleepCallback[0x10];
    unsigned char postSleepCallback[0x10];
    int format;
    union {
        unsigned int flags;
        struct {
            signed int active : 1;
            signed int started : 1;
        } bits;
    } state;
    unsigned char padding30[0x18];
    int alarmNumber;
    u32 channelMask;
    int channelCount;
    unsigned char channelNumber[16];
} NNSSndStrm;

extern void SND_StopTimer();
extern void PM_DeletePreSleepCallback(void *callback);
extern void PM_DeletePostSleepCallback(void *callback);
extern u32 SND_GetCurrentCommandTag(void);
extern int SND_FlushCommand();
extern void SND_WaitForCommandProc(u32 tag);
extern void ShutdownStrm(NNSSndStrm *stream);

void ForceStopStrm(NNSSndStrm *stream)
{
    u32 commandTag;

    if (stream->state.bits.started) {
        asm {
            ldr r0, [stream, #0x48]
            mov r6, #1
            mov r1, #0
            mov r2, r6, lsl r0
            ldr r0, [stream, #0x4c]
            mov r3, r1
        }
        SND_StopTimer();
        PM_DeletePreSleepCallback(&stream->preSleepCallback);
        PM_DeletePostSleepCallback(&stream->postSleepCallback);
        stream->state.flags &= ~2U;

        commandTag = SND_GetCurrentCommandTag();
        asm {
            mov r0, r6
        }
        SND_FlushCommand();
        SND_WaitForCommandProc(commandTag);
    }

    ShutdownStrm(stream);
}
