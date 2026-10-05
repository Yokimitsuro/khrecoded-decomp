#include "nitro/types.h"

typedef struct PartyState {
    int mode;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern u32 GetBoundedEntryField(int index);
extern void SetSubModelsEnabled(u32 entry, int arg);
extern void Actor_SetModelSetsVisible(u32 entry, int arg);

void DispatchPartyEntryArgByMode(int index, int arg)
{
    switch (data_ov001_020a04bc->mode) {
    case 0:
    case 2:
        SetSubModelsEnabled(GetBoundedEntryField(index), arg);
        break;
    case 1:
        Actor_SetModelSetsVisible(GetBoundedEntryField(index), arg);
        break;
    }
}
