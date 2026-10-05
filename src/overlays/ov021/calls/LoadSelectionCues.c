#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[10];
} CueEntry;

typedef struct {
    CueEntry entries[21];
    u8 pad_fc[4];
    int count;
    CueEntry extra;
} CueList;

typedef struct {
    u8 kind;
    u8 pad_01[0x2b];
    CueList cues;
} SelectionRecord;

typedef struct {
    u32 index;
    u32 arg;
} SelectionRef;

typedef struct {
    void **handlers;
    int handlerCount;
    u32 unk_08;
    void *extraHandler;
    u8 pad_10[4];
    u32 selection;
    u32 selectionArg;
    int layoutX;
    int layoutY;
} CuePlayer;

extern char sOv021_BaChDaZ_020b52a4[];
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *func_0202c4a0(const char *path, u32 mode);
extern void *RelocateResourceOffsets(void *header);
extern void *SpawnCueHandler(CueEntry *source, CuePlayer *owner, SelectionRef *arg, void *table);

void LoadSelectionCues(CuePlayer *player, SelectionRef *ref) {
    u8 kind = GetOverlaySelectionRecord(ref->index)->kind;
    void *block;
    void *table;
    SelectionRecord *record;
    CueList *cues;
    BOOL hasExtra;
    int i;
    u32 index = ref->index;
    player->selection = index;
    player->selectionArg = ref->arg;
    hasExtra = FALSE;
    player->unk_08 = 0;
    record = GetOverlaySelectionRecord(index);
    cues = &record->cues;
    if (cues->extra.id != -1) {
        hasExtra = TRUE;
    }
    if (cues->count <= 0 && !hasExtra) {
        return;
    }
    switch (kind) {
    case 0:
        player->layoutX = 0xf;
        player->layoutY = 0;
        break;
    case 1:
        player->layoutX = 2;
        player->layoutY = 0;
        break;
    case 2:
        player->layoutX = 0;
        player->layoutY = 0x12;
        break;
    }
    player->handlerCount = cues->count;
    if (hasExtra) {
        player->handlerCount++;
    }
    player->handlers = NNSi_FndAllocFromDefaultHeap(player->handlerCount << 2);
    i = 0;
    player->extraHandler = NULL;
    block = func_0202c4a0(sOv021_BaChDaZ_020b52a4, 0x11);
    table = RelocateResourceOffsets(block);
    for (; i < cues->count; i++) {
        player->handlers[i] = SpawnCueHandler(&cues->entries[i], player, ref, table);
    }
    if (hasExtra) {
        player->handlers[cues->count] = SpawnCueHandler(&cues->extra, player, ref, table);
        player->extraHandler = player->handlers[cues->count];
    }
    NNSi_FndFreeFromDefaultHeap(block);
}
