#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad00[0x2c];
    u16 resultTag;
    u16 pad2e;
    s32 resultValue;
} ScriptVm;

typedef struct StageEntry {
    u8 pad000[0x9c0];
    s32 kind;
} StageEntry;

extern u32 CacheStageEntryValue(u32 id);

u32 ScriptOp_IsStageEntryKind24(ScriptVm *vm)
{
    BOOL isKind = TRUE;
    StageEntry *entry = (StageEntry *)CacheStageEntryValue(1);
    if (entry == NULL) {
        return 0;
    }
    if (entry == NULL) {
        return 0;
    }
    vm->resultTag = 1;
    if (entry->kind != 0x18) {
        isKind = FALSE;
    }
    vm->resultValue = isKind;
    return 0;
}
