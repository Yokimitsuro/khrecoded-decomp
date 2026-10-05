#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    s32 busy;
} LinkOwner;

typedef struct {
    LinkOwner *owner;
    int kind;
} FieldLink;

typedef struct {
    u8 pad_00[0xbd];
    u8 lowBits : 4;
    u8 phase : 4;
    u8 pad_be[2];
    u32 flags;
} FieldUnit;

extern void StartFieldObjectFall(FieldUnit *unit);

void OnFieldUnitPushedUp(void *self, void *other, VecFx32 *push, FieldLink *link, FieldUnit *unit)
{
    if (unit->flags & 0x100) {
        return;
    }
    switch (unit->phase) {
    case 3:
    case 4:
        if (link != NULL && link->kind == 2 && link->owner->busy == 0 && push->x == 0 && push->y > 0 &&
            push->z == 0) {
            StartFieldObjectFall(unit);
        }
        break;
    }
}