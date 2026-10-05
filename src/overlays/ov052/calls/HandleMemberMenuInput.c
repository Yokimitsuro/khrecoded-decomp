#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x9b4];
    u8 pool;
    u8 pad_9b5[3];
    int autoSelect;
    u8 pad_9bc[0x1034 - 0x9bc];
    s8 activeSlot;
    u8 menuValue;
    s8 pendingSlot;
} MenuActor;

extern void *func_ov001_0206db78(int pool);
extern u16 SharedObject_GetId(void *self);
extern BOOL HasFlagsAt0xc(void *holder, u16 mask);
extern int GetSelectedMenuEntryValue(void);
extern BOOL func_ov021_020a755c(void *self);
extern void FieldMenu_TryOpenByMode(void);
extern int func_ov001_02078494(void);
extern int func_ov001_02078898(void);
extern void PlaySoundChecked(void *ptr, int arg);
extern int func_ov001_02063a38(void);
extern void SetFieldMenuMode_02078360(int mode, int arg);
extern BOOL IsField1078Clear(MenuActor *actor);
extern BOOL CanUseMemberSlot(MenuActor *actor, int index);

BOOL HandleMemberMenuInput(MenuActor *actor)
{
    void *self = func_ov001_0206db78(actor->pool);
    BOOL result = FALSE;
    BOOL useSlot;
    int slot;

    if (SharedObject_GetId(self) != 0) {
        return result;
    }
    if (HasFlagsAt0xc(self, 0x400)) {
        useSlot = FALSE;
        if (actor->autoSelect == 0) {
            slot = GetSelectedMenuEntryValue();
        } else {
            slot = actor->activeSlot;
        }
        if (slot >= 0) {
            useSlot = TRUE;
        } else if (!func_ov021_020a755c(self)) {
            FieldMenu_TryOpenByMode();
        }
        switch (func_ov001_02078494()) {
        case 2:
            actor->menuValue = func_ov001_02078898();
            PlaySoundChecked(NULL, 1);
            break;
        case 0:
            if (func_ov001_02063a38() == 6 && slot >= 0) {
                SetFieldMenuMode_02078360(2, 1);
                useSlot = FALSE;
                PlaySoundChecked(NULL, 1);
            }
            break;
        case 1:
            if (IsField1078Clear(actor)) {
                actor->pendingSlot = slot;
                actor->activeSlot = -1;
                result = TRUE;
            }
            useSlot = FALSE;
            break;
        }
        if (useSlot && CanUseMemberSlot(actor, slot)) {
            actor->activeSlot = slot;
            actor->pendingSlot = -1;
            result = TRUE;
        }
    }
    return result;
}
