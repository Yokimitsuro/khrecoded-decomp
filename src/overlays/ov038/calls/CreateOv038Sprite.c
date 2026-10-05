#include "nitro/types.h"

typedef struct Ov038SpriteDesc {
    s32 resourceA;
    s32 resourceB;
    s32 x;
    s32 y;
    u8 pad_10[0x04];
    BOOL markRecord;
    u32 priority;
} Ov038SpriteDesc;

typedef struct Ov038Sprite {
    s32 recordIndex;
    s32 x;
    s32 y;
    s32 offsetX;
    s32 offsetY;
} Ov038Sprite;

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
    Ov038Sprite topSprites[3];
    Ov038Sprite bottomSprites[3];
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern s32 PXI_Init_0204f0c8(Ov038SpritePool *pool, s32 resourceA, s32 resourceB);
extern void func_0204f218(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void IndexedRecord_ClearActive(Ov038SpritePool *pool, s32 recordIndex);
extern void Slot_SetMode2Bit(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void IndexedRecords_SetFlag2(Ov038SpritePool *pool, s32 recordIndex, s32 value);
extern void func_0204f18c(Ov038SpritePool *pool, s32 recordIndex, s32 scale);
extern void IndexedRecord_SetActive(Ov038SpritePool *pool, s32 recordIndex);
extern void SetOv038SpritePosition(s32 poolIndex, s32 spriteIndex, s32 x, s32 y);

void CreateOv038Sprite(s32 poolIndex, s32 spriteIndex, Ov038SpriteDesc *desc)
{
    Ov038Context *context = data_ov038_020bd164;
    Ov038SpritePool *pool = &context->pools[poolIndex];
    Ov038Sprite *sprite;
    s32 recordIndex;

    if (poolIndex == 0) {
        sprite = &context->topSprites[spriteIndex];
    } else {
        sprite = &context->bottomSprites[spriteIndex];
    }
    recordIndex = PXI_Init_0204f0c8(pool, desc->resourceA, desc->resourceB);
    func_0204f218(pool, recordIndex, 0);
    IndexedRecord_ClearActive(pool, recordIndex);
    Slot_SetMode2Bit(pool, recordIndex, 0);
    IndexedRecords_SetFlag2(pool, recordIndex, 1);
    func_0204f18c(pool, recordIndex, (u8)desc->priority);
    if (desc->markRecord != 0) {
        IndexedRecord_SetActive(pool, recordIndex);
    }
    sprite->recordIndex = recordIndex;
    sprite->x = desc->x;
    sprite->y = desc->y;
    sprite->offsetX = 0;
    sprite->offsetY = 0;
    SetOv038SpritePosition(poolIndex, spriteIndex, desc->x, desc->y);
}
