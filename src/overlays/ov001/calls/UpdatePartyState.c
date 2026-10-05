#include "nitro/types.h"

typedef struct ActorProfile {
    u16 unk0;
    u16 characterId;
    u16 level;
} ActorProfile;

typedef struct PartyActor {
    u8 pad_000[0x1d4];
    ActorProfile *profile;
} PartyActor;

typedef struct PartyEntry {
    int id;
    PartyActor *actor;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyState {
    int selected;
    PartyEntry entries[3];
    int count;
} PartyState;

typedef struct StatusRecord {
    u8 pad_0[4];
    u16 value;
} StatusRecord;

extern PartyState *NNSi_FndGetCurrentRootHeap(void);
extern BOOL func_ov021_020af408(void);
extern u8 func_ov001_0207b484(void);
extern BOOL Camera_IsFlag19Set(void);
extern void TogglePanelFormation(void);
extern StatusRecord *GetMapFinalStats(void);
extern u8 *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern s32 ScaleByKindAndMode(int kind, s32 value);
extern int func_ov001_0207162c(int index, int level, int characterId, int scaled);
extern BOOL IsHudFlag9Set(void);
extern void UpdateChannelLevel(int index, int characterId);
extern void func_ov001_02074fa8(int index, int characterId, int mode);
extern void RefreshActiveMenuEntry(int index, int x, int y);
extern void UpdatePrimaryEventRecord(void);
extern void func_ov001_0206d2dc(void);

int UpdatePartyState(void) {
    PartyState *party = NNSi_FndGetCurrentRootHeap();
    int i;

    if (party->entries[0].actor != NULL && (party->entries[0].flags & 0x10) <= 0) {
        BOOL ready = TRUE;
        if (func_ov021_020af408()) {
            ready = FALSE;
        }
        if (ready) {
            BOOL toggle = FALSE;
            if (func_ov001_0207b484() == 1 && !Camera_IsFlag19Set()) {
                toggle = TRUE;
            } else if (func_ov001_0207b484() == 2 && Camera_IsFlag19Set()) {
                toggle = TRUE;
            }
            if (toggle) {
                TogglePanelFormation();
            }
        }
    }
    for (i = 0; i < party->count; i++) {
        PartyEntry *entry = &party->entries[i];
        if (entry->actor != NULL) {
            StatusRecord *status = GetMapFinalStats();
            u8 *selection = GetOverlaySelectionRecord(i);
            u16 level = entry->actor->profile->level;
            s32 scaled = ScaleByKindAndMode(*selection, status->value);
            u16 characterId;
            func_ov001_0207162c(i, level, entry->actor->profile->characterId, scaled);
            characterId = entry->actor->profile->characterId;
            if (IsHudFlag9Set()) {
                UpdateChannelLevel(i, characterId);
                func_ov001_02074fa8(i, characterId, 7);
            } else {
                RefreshActiveMenuEntry(i, characterId, 7);
            }
        }
    }
    switch (party->selected) {
    case 0:
    case 2:
        UpdatePrimaryEventRecord();
        break;
    case 1:
        func_ov001_0206d2dc();
        break;
    }
    return 0;
}
