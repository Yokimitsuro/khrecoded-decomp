#include "nitro/types.h"

typedef struct SoundStreamHandle {
    u32 value;
} SoundStreamHandle;

extern u8 *gSoundWork;

SoundStreamHandle *GetSoundStreamHandle(u32 index)
{
    return (SoundStreamHandle *)(gSoundWork + 0xb44c0) + index;
}
