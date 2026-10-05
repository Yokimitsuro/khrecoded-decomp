#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} PointInt;

typedef struct {
    int recordIndex;
    int x;
    int y;
    int pad[2];
} SpriteSlot;

typedef struct {
    char records[0x6434];
} RecordBank;

typedef struct {
    char pad0[0x174];
    RecordBank banks[2];
    char pad1[0xc9dc - 0x174 - 2 * 0x6434];
    SpriteSlot slots[1];
} MenuWork;

extern void IndexedRecord_SetPair(void *recordBase, int recordIndex, PointInt *value);

#define F32_TO_FX32(v) ((int)((v) > 0 ? 0.5f + 4096.0f * (v) : 4096.0f * (v) - 0.5f))

void SetSlotPosition_020bf7d4(int bank, int slotIndex, int x, int y, MenuWork *work) {
    RecordBank *target = &work->banks[bank];
    SpriteSlot *slot = bank == 0 ? &work->slots[slotIndex] : NULL;
    PointInt fxPos;
    slot->x = x;
    slot->y = y;
    fxPos.x = F32_TO_FX32((float)slot->x);
    fxPos.y = F32_TO_FX32((float)slot->y);
    IndexedRecord_SetPair(target, slot->recordIndex, &fxPos);
}
