#include "nitro/types.h"

typedef struct PartyState {
    int mode;
} PartyState;

extern PartyState *data_ov001_020a04bc;
extern u32 GetBoundedEntryField(int index);
extern int func_ov052_020cfb48(u32 entry);
extern int Actor_AnyAnimSlotBusy(u32 entry);

int DispatchPartyEntryByMode(int index)
{
    switch (data_ov001_020a04bc->mode) {
    case 0:
    case 2:
        return func_ov052_020cfb48(GetBoundedEntryField(index));
    case 1:
        return Actor_AnyAnimSlotBusy(GetBoundedEntryField(index));
    }
    return 0;
}
