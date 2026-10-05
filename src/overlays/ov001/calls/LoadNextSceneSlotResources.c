#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) \
    (((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000) | ((index) & 0x1ff))

typedef struct SceneResourceEntry {
    u16 unk_00;
    u16 primaryFile;
    u16 secondaryFile;
    u16 unk_06;
} SceneResourceEntry;

typedef struct SceneResourceTable {
    u16 unk_00;
    u16 count;
    u8 pad_04[0x20];
    SceneResourceEntry *entries;
} SceneResourceTable;

typedef struct SceneSlot {
    u8 node[0x104];
    u8 flags;
    u8 pad_105[3];
} SceneSlot;

typedef struct SceneContext {
    u8 pad_00[8];
    s32 archive;
    u8 pad_0C[0xc];
    SceneSlot slots[16];
    u8 pad_1098[0x21];
    s8 loadCursor;
} SceneContext;

typedef struct SceneLoadRequest {
    u8 active;
    s8 slotIndex;
    u8 pad_02[2];
    void *primaryRecord;
    u32 secondaryFile;
    SceneResourceEntry *entry;
} SceneLoadRequest;

extern void *SND_RegisterSeq(u32 fileId, int flags);
extern u32 func_0202c4a0(u32 fileId, u32 flags);

BOOL LoadNextSceneSlotResources(SceneLoadRequest *request, SceneResourceTable *table, SceneContext *ctx) {
    s32 index;

    for (index = ctx->loadCursor; index < table->count; index = ctx->loadCursor) {
        SceneResourceEntry *entry;
        SceneSlot *slot;

        entry = &table->entries[index];
        slot = &ctx->slots[index];
        ctx->loadCursor++;
        if (!(slot->flags & 8)) {
            if (request->primaryRecord == NULL) {
                request->primaryRecord = SND_RegisterSeq(
                    ARCHIVE_FILE_ID(ctx->archive, entry->primaryFile), 0);
            }
            if (request->secondaryFile == 0) {
                request->secondaryFile = func_0202c4a0(ARCHIVE_FILE_ID(ctx->archive, entry->secondaryFile), 0);
            }
            request->entry = entry;
            request->slotIndex = ctx->loadCursor - 1;
            request->active = 1;
            return TRUE;
        }
        slot->flags = 8;
    }
    return FALSE;
}
