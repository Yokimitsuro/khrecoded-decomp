#include "nitro/types.h"

typedef struct EventContext {
    s32 mode;
} EventContext;

extern EventContext *data_ov001_020a04bc;
extern u32 GetBoundedEntryField(int index);

u32 GetEntryFieldForMode(int index)
{
    switch (data_ov001_020a04bc->mode) {
    case 0:
    case 2:
        return GetBoundedEntryField(index) + 0x230;
    case 1:
        return GetBoundedEntryField(index) + 0x230;
    }
    return 0;
}
