#include "nitro/types.h"

extern s32 LookupTableOffset(s32 category, s32 entryIndex);
extern BOOL IsRecordFlagBitSet(s32 recordId);

BOOL IsCategoryEntryFlagSet(s32 category, s32 entryIndex) {
    s32 recordId = LookupTableOffset(category, entryIndex);
    if (entryIndex < 0) {
        return FALSE;
    }
    return IsRecordFlagBitSet(recordId);
}
