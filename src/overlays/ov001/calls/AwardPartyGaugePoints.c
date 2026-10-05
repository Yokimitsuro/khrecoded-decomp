#include "nitro/types.h"

typedef struct GaugeFlash {
    u32 elapsed;
    u16 unk_04;
    u16 duration;
} GaugeFlash;

typedef struct GaugeHud {
    u8 pad_0000[0x10d4];
    GaugeFlash flash;
} GaugeHud;

typedef struct FieldManager {
    int mode;
    u32 unk_04;
    GaugeHud *hud;
} FieldManager;

typedef struct PartyEntry {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x4c];
    int (*getState)(struct PartyEntry *entry);
} PartyEntry;

extern FieldManager *data_ov001_020a04bc;
extern BOOL IsFieldFlag16Set(void);
extern s32 func_ov001_02063a38(void);
extern PartyEntry *GetBoundedEntryField(int index);
extern u32 func_ov001_02075248(int index);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov001_0206e224(void);
extern void func_ov001_02073074(int delta, BOOL loadNow);

void AwardPartyGaugePoints(int index, int points)
{
    FieldManager *manager = data_ov001_020a04bc;
    PartyEntry *entry;
    s32 phase;
    int state;
    GaugeFlash *flash;

    if (manager == NULL || IsFieldFlag16Set()) {
        return;
    }
    phase = func_ov001_02063a38();
    if (phase != 0 && phase != 8 && phase != 10) {
        return;
    }
    entry = GetBoundedEntryField(index);
    if (entry == NULL) {
        return;
    }
    if (func_ov001_02075248(index) && IsPlayerEntryFlagSet(index, 0x20)) {
        points += (points << 11) >> 12;
    }
    if (entry->getState != NULL) {
        state = entry->getState(entry);
    } else {
        state = entry->state;
    }
    if (state == 10) {
        points = 0;
    }
    if (!func_ov001_0206e224()) {
        points = 0;
    }
    if (points != 0) {
        func_ov001_02073074(points, FALSE);
    }
    if (manager->mode == 0 || manager->mode == 2) {
        flash = &manager->hud->flash;
        flash->duration = 150;
        flash->elapsed = 0;
    }
}
