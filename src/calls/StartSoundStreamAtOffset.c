#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct NNSSndStrmHandle {
    void *player;
} NNSSndStrmHandle;

typedef struct {
    u8 pad_00000[0xb44c0];
    NNSSndStrmHandle streamHandles[2];
    u8 pad_b44c8[0xb47d8 - 0xb44c8];
    u8 currentStrmNo;
} SoundWork;

extern SoundWork *data_0206084c;
extern BOOL NNS_SndArcStrmStart(NNSSndStrmHandle *handle, int strmNo, u32 offset);

void StartSoundStreamAtOffset(int handleIndex, u32 offset)
{
    NNS_SndArcStrmStart(&data_0206084c->streamHandles[handleIndex], data_0206084c->currentStrmNo, offset);
}
