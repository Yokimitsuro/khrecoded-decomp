#include "nitro/types.h"

typedef struct SlotPosition {
    s32 x;
    s32 y;
} SlotPosition;

extern int PXI_Init_0204f0c8(void *manager, int resource, int animation);
extern void IndexedRecord_SetPair(void *manager, int slotIndex, SlotPosition *position);
extern void Slot_SetMode2Bit(void *manager, int slotIndex, int mode);
extern void func_0204f18c(void *manager, int slotIndex, int priority);
extern void IndexedRecord_ClearActive(void *manager, int slotIndex);
extern void func_0204f218(void *manager, int slotIndex, int palette);
extern void IndexedRecords_SetFlag2(void *manager, int slotIndex, int enabled);

int CreateObjectSlot_020bdec4(void *manager, int animation, int resource, int x, int y, int mode,
                              int priority, int palette, int enabled) {
    int slotIndex = PXI_Init_0204f0c8(manager, resource, animation);
    SlotPosition position;
    position.x = x << 12;
    position.y = y << 12;
    IndexedRecord_SetPair(manager, slotIndex, &position);
    Slot_SetMode2Bit(manager, slotIndex, mode);
    func_0204f18c(manager, slotIndex, (u8)priority);
    if (palette >= 0) {
        IndexedRecord_ClearActive(manager, slotIndex);
        func_0204f218(manager, slotIndex, (u16)palette);
    }
    IndexedRecords_SetFlag2(manager, slotIndex, enabled);
    return slotIndex;
}
