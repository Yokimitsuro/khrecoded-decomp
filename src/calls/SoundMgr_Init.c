#include "nitro/types.h"

typedef struct SoundSlot {
    struct SoundSlot *next;
    struct SoundSlot *prev;
    u8 pad_08[0xe];
    s16 id;
    u8 pad_18[4];
    u8 queue[4];
} SoundSlot;

extern u8 *data_0206084c;
extern char sMain_SdSoundDataSdat_02056134[];

extern void SoundMgr_WaitLoaderIfState1(void);
extern void NNS_SndPlayerStopSeqAll(int arg);
extern void NNS_SndInit(void);
extern void NNS_SndArcInit(void *archive, const char *path, void *heap, BOOL loadSymbols);
extern void NNS_SndArcSetLoadBlockSize(u32 size);
extern void NNS_SndArcPlayerSetup(void *heap);
extern void Word_Clear(void *list);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void NNS_SndArcStrmInit(int priority, void *heap);
extern void Word_ClearB(void *handle);
extern BOOL NNS_SndArcLoadBank(int seqNo, void *heap);
extern int NNS_SndHeapSaveState(void *heap);

void SoundMgr_Init(const char *path, BOOL loadSymbols)
{
    u8 *base = data_0206084c;
    SoundSlot *slots;
    int i;

    if (path == NULL) {
        path = sMain_SdSoundDataSdat_02056134;
    }
    SoundMgr_WaitLoaderIfState1();
    NNS_SndPlayerStopSeqAll(0);
    NNS_SndInit();
    NNS_SndArcInit(base, path, *(void **)(base + 0xb04b4), loadSymbols);
    NNS_SndArcSetLoadBlockSize(0x400);
    NNS_SndArcPlayerSetup(*(void **)(base + 0xb04b4));
    Word_Clear(base + 0xb44d8);
    Word_Clear(base + 0xb44dc);
    MI_CpuFill8(base + 0xb4518, 0, sizeof(SoundSlot) * 16);
    slots = (SoundSlot *)(base + 0xb4518);
    for (i = 0; i < 16; i++) {
        *(SoundSlot **)(base + i * 0x20 + 0xb4518) = i < 15 ? &slots[i + 1] : NULL;
        *(SoundSlot **)(base + i * 0x20 + 0xb451c) = i > 0 ? &slots[i - 1] : NULL;
        *(s16 *)(base + i * 0x20 + 0xb452e) = i + 6;
        Word_Clear(base + 0xb4534 + i * 0x20);
    }
    *(SoundSlot **)(base + 0xb4718) = (SoundSlot *)(base + 0xb4518);
    NNS_SndArcStrmInit(10, *(void **)(base + 0xb44bc));
    Word_ClearB(base + 0xb44c0);
    Word_ClearB(base + 0xb44c4);
    *(s16 *)(base + 0xb472a) = -1;
    *(s16 *)(base + 0xb472c) = -1;
    *(s16 *)(base + 0xb4736) = -1;
    *(u16 *)(base + 0xb4734) = 0;
    NNS_SndArcLoadBank(0x29, *(void **)(base + 0xb04b4));
    *(int *)(base + 0xa8) = NNS_SndHeapSaveState(*(void **)(data_0206084c + 0xb04b4));
    *(int *)(base + 0xa0) = *(int *)(base + 0xa8);
    *(int *)(base + 0xa4) = -1;
}
