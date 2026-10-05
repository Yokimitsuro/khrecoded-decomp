#include "nitro/types.h"

typedef struct BattleEntry {
    u8 pad_00[0x90];
} BattleEntry;

typedef struct BattleContext {
    u8 pad_00[0x6c];
    BattleEntry *entries;
} BattleContext;

typedef struct CommandBuffer {
    u8 data[0x20];
} CommandBuffer;

typedef struct BattleScene BattleScene;
struct BattleScene {
    u8 pad_000[0x234];
    u32 flags;
    u8 pad_238[0x768 - 0x238];
    int isActive;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 commandKind;
    u8 pad_9b5[0xa51 - 0x9b5];
    s8 entryIndex;
    u8 pad_a52[0x1078 - 0xa52];
    BattleContext *context;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(BattleScene *scene, int mode);
    u8 pad_10f0[0x10f8 - 0x10f0];
    void (*updateCallback)(BattleScene *scene);
};

extern void func_ov052_020cfdd4(BattleScene *scene, BattleEntry *entry, int arg);
extern void ApplyAnimRootMotion(BattleScene *scene, BattleEntry *entry);
extern void func_ov052_020d1a88(CommandBuffer *buffer, BattleEntry *entry, int arg, BattleContext *context, u8 kind);
extern BOOL ProcessTargetHitEntries(BattleScene *scene, BattleEntry *entry, CommandBuffer *buffer);
extern BOOL UpdateActionPhase(BattleScene *scene, BattleEntry *entry, int arg);
extern BOOL HandlePendingCommand(BattleScene *scene);
extern void FireLinkedShot(BattleScene *scene);

void PrepareEntryCommandAndSetMode(BattleScene *scene)
{
    BattleContext *context = scene->context;
    BattleEntry *entries = context->entries;
    int entryIndex = scene->entryIndex;
    CommandBuffer buffer;
    u32 hasFlag;

    func_ov052_020cfdd4(scene, &entries[entryIndex], 0);
    ApplyAnimRootMotion(scene, &entries[entryIndex]);
    func_ov052_020d1a88(&buffer, &entries[entryIndex], 0, context, scene->commandKind);
    scene->updateCallback = FireLinkedShot;
    if (ProcessTargetHitEntries(scene, &entries[entryIndex], &buffer)) {
        return;
    }
    if (UpdateActionPhase(scene, &entries[entryIndex], 0)) {
        return;
    }
    if (scene->isActive == 0) {
        return;
    }
    hasFlag = scene->flags & 4;
    if (HandlePendingCommand(scene)) {
        return;
    }
    if (hasFlag) {
        scene->setMode(scene, 5);
        return;
    }
    scene->setMode(scene, 4);
}
