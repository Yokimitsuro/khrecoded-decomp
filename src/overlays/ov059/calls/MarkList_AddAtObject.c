#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MarkList MarkList;

typedef struct MarkSource {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0E0[0x150 - 0xe0];
    s32 *surfaceType;
} MarkSource;

extern s32 MapStateToOddIndex(s32 *surfaceType);
extern void MarkList_Add(MarkList *list, s32 markKind, VecFx32 *position);

void MarkList_AddAtObject(MarkList *list, MarkSource *source)
{
    s32 markKind = MapStateToOddIndex(source->surfaceType);

    MarkList_Add(list, markKind, &source->position);
}
