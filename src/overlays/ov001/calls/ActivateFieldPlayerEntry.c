#include "nitro/types.h"

typedef struct FieldPlayer FieldPlayer;

struct FieldPlayer {
    u8 pad_000[0x1d8];
    u8 slotIndex;
    u8 pad_1d9[0x20c - 0x1d9];
    void (*onStateChange)(FieldPlayer *player, int state, int flag);
    void (*onActivate)(FieldPlayer *player, int arg);
};

typedef struct {
    u8 pad_00[8];
    u8 cell[0x24 - 0x08];
    u16 flags;
    u8 pad_26[2];
} FieldPlayerEntry;

typedef struct {
    s32 mode;
    FieldPlayerEntry entries[1];
} FieldPlayerSet;

extern FieldPlayerSet *data_ov001_020a04bc;

extern FieldPlayer *GetBoundedEntryField(int index);
extern void func_ov021_020a7510(void *cell);
extern void func_ov001_0206cab4(int enabled);
extern void ApplyRecordTableEntry5(int index, int param2, int param3);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void func_ov001_0206d0ac(FieldPlayer *player);
extern void RefreshFieldMenuPage(FieldPlayer *player);

void ActivateFieldPlayerEntry(int index, u32 param, u16 arg) {
    FieldPlayerSet *set = data_ov001_020a04bc;
    FieldPlayerEntry *entry;
    FieldPlayer *current;
    FieldPlayer *player;

    if (set != NULL && (player = GetBoundedEntryField(index)) != NULL) {
        entry = &set->entries[index];
        entry->flags |= 2;
        entry->flags |= 8;
        entry->flags &= 0xffef;
        func_ov021_020a7510(entry->cell);
        current = GetBoundedEntryField(index);
        if (current->onStateChange != NULL) {
            current->onStateChange(current, 2, 1);
        }
        func_ov001_0206cab4(0);
        ApplyRecordTableEntry5(player->slotIndex, 0, param);
        ActorSlot_SetFlag8ByIndex(player->slotIndex, FALSE);
        if (player->onActivate != NULL) {
            player->onActivate(player, arg);
        }
        if (index == 0) {
            switch (set->mode) {
            case 0:
            case 2:
                func_ov001_0206d0ac(player);
                break;
            case 1:
                RefreshFieldMenuPage(player);
                break;
            }
        }
    }
}
