#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;
extern void StoreToGlobalPtr4Field28(s32 value);
extern void ActorRegistry_ClearCollisionResult(void);
extern void ReleaseSeqArcHeapLevel(s32 level);
extern void ReleaseOv038Context(void);

u32 DisableOv038Sound(void)
{
    ReleaseOv038Context();
    ActorRegistry_ClearCollisionResult();
    ReleaseSeqArcHeapLevel(1);
    StoreToGlobalPtr4Field28(1);
    data_ov038_020bd160->flags = data_ov038_020bd160->flags | 0x8000;
    return 5;
}
