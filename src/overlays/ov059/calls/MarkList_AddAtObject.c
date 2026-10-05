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
extern void func_ov059_020cdd88(MarkList *list, s32 markKind, VecFx32 *position);

void MarkList_AddAtObject(MarkList *list, MarkSource *source)
{
    s32 markKind = MapStateToOddIndex(source->surfaceType);

    func_ov059_020cdd88(list, markKind, &source->position);
}
