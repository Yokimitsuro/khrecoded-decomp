#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Pool1Entry {
    u32 id : 16;
    s32 type : 16;
    VecFx32 point;
    fx32 value;
} Pool1Entry;

void InitPool1Entry(Pool1Entry *entry, const VecFx32 *point, int type, fx32 value, int id)
{
    entry->id = id;
    entry->point = *point;
    entry->type = type;
    switch (type) {
    case 0:
        entry->value = value;
        break;
    case 1:
        entry->value = value;
        break;
    }
}
