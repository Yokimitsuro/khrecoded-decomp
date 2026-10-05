#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorEntry ActorEntry;

struct ActorEntry {
    u8 pad_000[0x200];
    void (*onRestore)(ActorEntry *entry, int arg);
};

typedef struct RestoreFlags {
    u8 unk_0 : 5;
    u8 pending : 1;
    u8 unk_6 : 2;
} RestoreFlags;

typedef union ResourceSlot {
    void *data;
    u32 handle;
} ResourceSlot;

typedef struct RestoreState {
    u8 pad_00[4];
    s8 level;
    u8 pad_05[3];
    VecFx32 positions[3];
    u16 angles[3];
    u8 pad_32[6];
    u8 motionStates[3][0x10];
    ResourceSlot resources[3];
    u8 pad_74[2];
    RestoreFlags flags;
} RestoreState;

typedef struct Session {
    u8 pad_0000[0x2740];
    RestoreState restore;
} Session;

extern Session *data_ov001_020a0480;
extern int func_ov001_0206dc38(void);
extern void func_ov001_02067fa4(int index, int level, VecFx32 *position, u16 *angle);
extern void func_ov001_0206dd90(int index, VecFx32 *position, u16 angle);
extern ActorEntry *GetBoundedEntryField(int index);
extern void ApplyModeCallbackAndBlock(ActorEntry *entry, void *resource, void *motionState);
extern void func_ov001_0206e444(s32 enable);
extern s32 func_ov001_02063a38(void);
extern void ForwardSubModeStart(void);

BOOL RestoreSessionActors(void) {
    Session *session = data_ov001_020a0480;
    RestoreState *restore = &session->restore;
    BOOL restored = FALSE;
    int i;

    if (restore->level > 0) {
        for (i = 0; i < func_ov001_0206dc38(); i++) {
            func_ov001_02067fa4(i, restore->level, &session->restore.positions[i], &session->restore.angles[i]);
        }
        restored = TRUE;
    }
    for (i = 0; i < func_ov001_0206dc38(); i++) {
        func_ov001_0206dd90(i, &session->restore.positions[i], session->restore.angles[i]);
        if (session->restore.resources[i].handle != 0) {
            ApplyModeCallbackAndBlock(GetBoundedEntryField(i), session->restore.resources[i].data, session->restore.motionStates[i]);
        } else {
            ActorEntry *entry = GetBoundedEntryField(i);
            if (entry->onRestore != NULL) {
                entry->onRestore(entry, 0);
            }
        }
        func_ov001_0206e444(1);
    }
    if (func_ov001_02063a38() != 6 && (restore->level > 0 || restore->flags.pending)) {
        ForwardSubModeStart();
        restore->flags.pending = 0;
    }
    return restored;
}
