#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef float f32;

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef struct {
    fx32 x;
    fx32 y;
} SlotPos;

typedef struct {
    u8 pad_00[0xc];
    void *objManager;
    u8 pad_10[4];
    SlotPos pos;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void IndexedRecord_SetPair(void *objManager, int slotIndex, SlotPos *pos);

void SetPopupSlotPos(int slotIndex, int x, int y, int offsetX, int offsetY)
{
    PopupManager *manager = data_ov091_020c375c;
    void *objManager = manager->objManager;
    SlotPos *pos = &manager->pos;

    pos->x = INT_TO_FX32(x + offsetX);
    pos->y = INT_TO_FX32(y + offsetY);
    IndexedRecord_SetPair(objManager, slotIndex, pos);
}
