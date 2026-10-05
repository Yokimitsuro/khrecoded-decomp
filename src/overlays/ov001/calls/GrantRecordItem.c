#include "nitro/types.h"

typedef struct RecordGrant {
    u16 itemId;
    u8 level;
    u8 kind;
} RecordGrant;

extern int func_ov001_02064a38(RecordGrant *grant, int notify);

void GrantRecordItem(u16 itemId)
{
    RecordGrant grant;

    grant.itemId = itemId;
    grant.level = 0;
    grant.kind = 0;
    func_ov001_02064a38(&grant, 0);
}
