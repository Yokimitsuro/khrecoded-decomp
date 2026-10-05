#include "nitro/types.h"

typedef struct {
    int value;
    u8 pad_04[8];
} ObjectSlot;

typedef struct {
    u8 pad_00[0x8c];
    ObjectSlot slots[8];
    u8 pad_EC[0x1c];
    int activeSlots;
} ScriptObject;

extern void func_ov021_020addec(void *owner, ScriptObject *object);

void ResetObjectSlots(void *owner, ScriptObject *object) {
    int i;

    for (i = 0; i < 8; i++) {
        object->slots[i].value = 0;
    }
    object->activeSlots = 0;
    func_ov021_020addec(owner, object);
}
