#include "nitro/types.h"

typedef struct SpriteCell {
    u8 pad_00[4];
    u16 width;
    u16 height;
    u32 attributes;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 pad_25[7];
    void *cellKey;
} SpriteCell;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 startValue;
    s32 endValue;
    u8 pad_10[0xc];
} Tween;

typedef struct SpritePair {
    SpriteCell small;
    SpriteCell large;
    Tween tween;
} SpritePair;

extern void *NestedPointer_GetFirstWord(void *resource, int recordIndex, int entryIndex);
extern void SetSlotKeyAndRebind(SpriteCell *cell, void *cellKey, int mode);
extern void func_020524fc(Tween *tween);

void InitSpritePairFromResource(SpritePair *pair, void *resource)
{
    SetSlotKeyAndRebind(&pair->small, NestedPointer_GetFirstWord(resource, 7, 0), 0);
    SetSlotKeyAndRebind(&pair->large, NestedPointer_GetFirstWord(resource, 7, 1), 0);
    pair->small.width = 0x10;
    pair->small.height = 0x10;
    pair->large.width = 0x20;
    pair->large.height = 0x20;
    pair->small.attributes |= 0xa0000;
    pair->large.attributes |= 0xf0000;
    pair->small.unk_24 = 0x3f;
    pair->large.unk_24 = 0x3f;
    func_020524fc(&pair->tween);
}
