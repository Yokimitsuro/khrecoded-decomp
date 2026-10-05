#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageLink {
    u16 lowBits : 11;
    u16 stageEntry : 3;
    u16 highBits : 2;
    u8 pad_02[0x32];
    VecFx32 position;
} StageLink;

typedef struct StageActor {
    u8 pad_000[0x1D2];
    u16 recordId;
    u8 pad_1D4[0xB8];
    StageLink link;
} StageActor;

typedef struct StageEntry {
    u8 pad_000[0x21C];
    u32 (*getFlags)(struct StageEntry *entry);
} StageEntry;

extern u8 *GetStageEventRecord(u32 id);
extern u32 func_ov001_0206dc38(void);
extern StageEntry *GetBoundedEntryField(int index);
extern void RandomHorizontalVector(fx32 length, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SyncStageEntryPosition(u32 id, VecFx32 *outPosition);
extern void ChooseWanderDestination(u8 *record, StageActor *actor, VecFx32 *position);

void ResolveStageActorSpawnPos(StageActor *actor, int unused, VecFx32 *position)
{
    u8 *record = GetStageEventRecord(actor->recordId);
    StageEntry *entry;
    u32 flags;
    VecFx32 offset;

    if ((int)func_ov001_0206dc38() > 0) {
        entry = GetBoundedEntryField((u16)(actor->link.stageEntry - 1));
        if (entry != NULL) {
            if (entry->getFlags != NULL) {
                flags = entry->getFlags(entry);
            } else {
                flags = 0;
            }
            if (flags & 0x40) {
                RandomHorizontalVector(0x2000, &offset);
                VEC_Add(&actor->link.position, &offset, position);
                return;
            }
        }
    }
    SyncStageEntryPosition(actor->link.stageEntry, position);
    ChooseWanderDestination(record, actor, position);
}
