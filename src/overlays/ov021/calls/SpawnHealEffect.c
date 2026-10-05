#include "nitro/types.h"

typedef struct EffectRequest {
    u8 id;
    u8 pad_01[3];
    s32 offsetX;
    s32 offsetY;
    s32 offsetZ;
    s16 scale;
    u8 pad_12[2];
    s32 rate;
    u8 pad_18[0xc];
    u8 looped;
    u8 visible;
    s16 count;
    s16 prevIndex;
    s16 index;
} EffectRequest;

typedef struct BigObject {
    u8 pad_000[0x1d8];
    u8 effectId;
} BigObject;

extern void ResetAnimationTrackState(EffectRequest *request);
extern int func_ov001_0206db8c(int index);
extern int func_ov021_020a8cc0(EffectRequest *request, int groupId);

void SpawnHealEffect(BigObject *obj)
{
    EffectRequest request;

    ResetAnimationTrackState(&request);
    request.id = obj->effectId;
    request.visible = 1;
    request.count = 1;
    request.looped = 0;
    request.offsetZ = 0;
    request.offsetY = 0;
    request.offsetX = 0;
    func_ov021_020a8cc0(&request, func_ov001_0206db8c(1));
}
