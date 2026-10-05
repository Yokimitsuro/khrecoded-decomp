#include "nitro/types.h"

typedef struct StageSource {
    u16 unk00;
    u16 entryCount;
} StageSource;

typedef struct StageState {
    u8 pad_0000[4];
    void *loader;
    u8 pad_0008[0x200];
    void *entries;
    void *entryRefs;
    u8 pad_0210[0x18de6 - 0x210];
    u16 entryCount;
    u16 cursor;
    u16 selection;
    u16 pad_18dec;
    u16 scroll;
    u8 pad_18df0[8];
    StageSource *source;
    u8 pad_18dfc[0x18f4c - 0x18dfc];
    void *handlers[5];
} StageState;

extern StageState *data_ov001_020a0528;
extern void func_ov001_0209c3e8(void);
extern void CacheStageEntrySlot(int slot);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02064784(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void Obj_SetWord14(void *loader, void *callback);
extern void AnimSequence_Init(void);
extern void InitPathCursor(void);
extern void AnimSequence_Update(void);
extern void GetStageJointPosition(void);
extern void AddTouchPoint(void);
extern void AnimSequence_Init_020a1ac8(void);
extern void AnimSequence_Reset(void);
extern void AnimSequence_Update_020a1b70(void);
extern void AnimSequence_GetCurrentPosition(void);
extern void AnimSequence_AddClip(void);
extern void UpdateStageEventSpawns(void);

void BeginStageEntries(StageSource *source)
{
    func_ov001_0209c3e8();
    if (source == NULL) {
        return;
    }
    data_ov001_020a0528->cursor = 0;
    data_ov001_020a0528->selection = 0;
    data_ov001_020a0528->scroll = 0;
    data_ov001_020a0528->source = source;
    CacheStageEntrySlot(0);
    CacheStageEntrySlot(1);
    CacheStageEntrySlot(2);
    if (func_ov001_02063a24()) {
        if (func_ov001_02064784() == 2) {
            data_ov001_020a0528->handlers[0] = AnimSequence_Init;
            data_ov001_020a0528->handlers[1] = InitPathCursor;
            data_ov001_020a0528->handlers[2] = AnimSequence_Update;
            data_ov001_020a0528->handlers[3] = GetStageJointPosition;
            data_ov001_020a0528->handlers[4] = AddTouchPoint;
        } else if (func_ov001_02064784() == 6) {
            data_ov001_020a0528->handlers[0] = AnimSequence_Init_020a1ac8;
            data_ov001_020a0528->handlers[1] = AnimSequence_Reset;
            data_ov001_020a0528->handlers[2] = AnimSequence_Update_020a1b70;
            data_ov001_020a0528->handlers[3] = AnimSequence_GetCurrentPosition;
            data_ov001_020a0528->handlers[4] = AnimSequence_AddClip;
        }
    }
    data_ov001_020a0528->entryCount = source->entryCount;
    data_ov001_020a0528->entries = NNSi_FndAllocFromDefaultHeap(data_ov001_020a0528->entryCount * 0x28);
    data_ov001_020a0528->entryRefs = NNSi_FndAllocFromDefaultHeap(data_ov001_020a0528->entryCount * 4);
    func_01ff88c4(data_ov001_020a0528->entries, 0, data_ov001_020a0528->entryCount * 0x28);
    func_01ff88c4(data_ov001_020a0528->entryRefs, 0, data_ov001_020a0528->entryCount * 4);
    Obj_SetWord14(data_ov001_020a0528->loader, UpdateStageEventSpawns);
}
