#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0xc];
    void *work;
    u32 unk_10;
    void *updateFunc;
    u8 pad_18[0x36];
    u16 flags;
    u8 pad_50[8];
    u32 mode : 15;
    u32 pendingDisable : 1;
    u32 unk_58_16 : 16;
    u8 pad_5c[4];
    int phase;
} FieldObject;

extern void func_ov001_0207f71c(FieldObject *object, BOOL enabled);
extern void ActorSlot_Unlink(void *slot);
extern int AdvanceWrappedPhase(FieldObject *object);
extern int FallFieldObject(FieldObject *object);

void FieldObject_SetPhaseMode(FieldObject *object, int mode)
{
    object->mode = mode;
    switch (mode) {
    case 0:
        object->updateFunc = AdvanceWrappedPhase;
        func_ov001_0207f71c(object, TRUE);
        return;
    case 1:
        object->updateFunc = FallFieldObject;
        object->phase = 0;
        func_ov001_0207f71c(object, TRUE);
        return;
    case 2:
        if (object->flags & 4) {
            ActorSlot_Unlink(object->work);
            func_ov001_0207f71c(object, FALSE);
            return;
        }
        object->pendingDisable = TRUE;
        return;
    }
}
