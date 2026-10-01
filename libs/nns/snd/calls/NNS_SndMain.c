typedef unsigned int u32;

extern const void *SND_RecvCommandReply(u32 flags);
extern int SND_FlushCommand();
extern void NNSi_SndPlayerMain(void);
extern void NNSi_SndCaptureMain(void);
extern void NNSi_SndArcStrmMain(void);

void NNS_SndMain(void)
{
    u32 flags = 0;

    while (SND_RecvCommandReply(flags) != 0) {
    }

    NNSi_SndPlayerMain();
    NNSi_SndCaptureMain();
    NNSi_SndArcStrmMain();
    asm {
        mov r0, flags
    }
    (void)SND_FlushCommand();
}
