#include "nitro/types.h"

typedef struct {
    u16 unk0;
    u8 flags;
    u8 unk3;
    void *record;
} EffectResource;

typedef struct {
    u8 pad_000[4];
    s8 areaId;
    u8 pad_005[0xb];
    EffectResource *resources[21];
    u8 pad_064[0x132 - 0x64];
    s16 savedValue;
    u8 savedAreaId;
} EffectManager;

extern EffectManager *data_ov001_020a04fc;
extern void func_ov001_02087010(void);
extern void ReleaseSharedRecordSlot(void *record);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern int func_ov001_020645c8(int flagId);
extern int func_ov001_020644c0(void);
extern void ClearSessionPackedBit(int flagId);
extern void DestroyAllEffectEntries(int mode);

void ReleaseEffectResources(void)
{
    EffectManager *manager = data_ov001_020a04fc;
    int i;

    func_ov001_02087010();
    for (i = 0; i < 21; i++) {
        EffectResource *resource = manager->resources[i];
        if (resource != NULL) {
            if (resource->flags & 1) {
                ReleaseSharedRecordSlot(resource->record);
            }
            NNSi_FndFreeFromDefaultHeap(resource);
            manager->resources[i] = NULL;
        }
    }
    if (func_ov001_020645c8(0x3614) == 0) {
        manager->savedValue = func_ov001_020644c0();
        manager->savedAreaId = manager->areaId;
    } else {
        ClearSessionPackedBit(0x3614);
    }
    DestroyAllEffectEntries(1);
}
