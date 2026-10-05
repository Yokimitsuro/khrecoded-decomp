#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x10];
    u16 actorId;
    u8 pad_12[0x5e];
    s32 progress;
    s32 limit;
} CommandEntry;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct {
    u8 pad_00000[0x18d7c];
    void *commandList;
} StageManager;

extern StageManager *func_ov001_0209c3e8(void);
extern void *func_ov001_0208f2a4(void *list);
extern CommandEntry *func_ov001_0208f290(void *list, void *node);
extern void *func_ov001_0208f2b4(void *node);
extern BOOL IsCommandType8(CommandEntry *entry);
extern StageActor *GetStageActor(int id);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_Mag(const VecFx32 *v);
extern int GetStageRowIndex(CommandEntry *entry);

int FindNearestCommandEntry(CommandEntry *target, int mode)
{
    StageManager *manager = func_ov001_0209c3e8();
    CommandEntry *found = 0;
    void *node;
    CommandEntry *entry;
    fx32 best;

    if (target == 0) {
        return (int)found;
    }
    node = func_ov001_0208f2a4(manager->commandList);
    while (node != 0) {
        entry = func_ov001_0208f290(manager->commandList, node);
        node = func_ov001_0208f2b4(node);
        if (IsCommandType8(entry) || entry->actorId == 0) {
            continue;
        }
        switch (mode) {
        case 0:
            if (entry != target) {
                StageActor *from = GetStageActor((s16)target->actorId);
                StageActor *to = GetStageActor((s16)entry->actorId);
                if (from != 0 && to != 0) {
                    VecFx32 offset;
                    fx32 distance;
                    VEC_Subtract(&from->position, &to->position, &offset);
                    offset.y = 0;
                    distance = VEC_Mag(&offset);
                    if (best == 0 || distance < best) {
                        best = distance;
                        found = entry;
                    }
                }
            }
            break;
        case 1:
            if (entry->progress < entry->limit) {
                if (best == 0 || entry->progress < best) {
                    best = entry->progress;
                    found = entry;
                }
            }
            break;
        }
    }
    if (found != 0) {
        return GetStageRowIndex(found);
    }
    return 0;
}

