#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactRef {
    void *contact;
    s32 kind;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[4];
    VecFx32 direction;
} ContactQuery;

extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);

BOOL IsQueryFacingContact(ContactRef *ref, ContactQuery *query) {
    if (IsFacingContactNormal(ref, &query->direction)) {
        return TRUE;
    }
    return FALSE;
}
