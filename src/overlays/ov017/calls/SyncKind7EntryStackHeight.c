#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Kind7Entry {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x2a];
    u8 slot;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0xc];
    s8 state;
    u8 pad_51[3];
    u16 flags;
    s16 belowIndex;
    u8 pad_58[2];
    s16 anchorIndex;
} Kind7Entry;

extern u8 *ActorRegistry_GetEntityByIndex(int slot);
extern Kind7Entry *func_ov001_02086384(void *owner, int index);
extern Kind7Entry *FindInactiveOwnerAncestor(Kind7Entry *entry);
extern void ResizeBoxCollisionObject(void *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void SyncKind7EntryStackHeight(Kind7Entry *entry)
{
    Kind7Entry *current;
    Kind7Entry *parent;
    u8 *actor;
    fx32 height;
    BOOL active;

    if (entry->flags & 1) {
        current = entry;
        height = 0;
        while (TRUE) {
            active = TRUE;
            if (current->state != 2 && current->state != 1) {
                active = FALSE;
            }
            if (!active) {
                height += 0x1800;
            }
            if (current->belowIndex < 0) {
                break;
            }
            current = func_ov001_02086384(current->owner, current->belowIndex);
        }
        if (height != 0) {
            actor = ActorRegistry_GetEntityByIndex(entry->slot);
            ResizeBoxCollisionObject(actor + 0x10c, 0x1800, height, 0x1800, 0);
            Obj_SetPosition(actor, &entry->position);
        }
    } else {
        active = TRUE;
        if (entry->state != 2 && entry->state != 1) {
            active = FALSE;
        }
        if (!active) {
            parent = FindInactiveOwnerAncestor(entry);
            if (parent != NULL) {
                entry->position.y = parent->position.y + 0x1800;
            } else {
                entry->position.y = func_ov001_02086384(entry->owner, entry->anchorIndex)->position.y;
            }
            Obj_SetPosition(ActorRegistry_GetEntityByIndex(entry->slot), &entry->position);
        }
    }
}
