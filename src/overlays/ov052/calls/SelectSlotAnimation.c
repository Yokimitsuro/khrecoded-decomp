#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 *anim;
    u8 *blendAnim;
} AnimEntry;

typedef struct {
    int kind;
    int type;
    u8 pad_08[0x18 - 0x08];
    AnimEntry **entries;
    int count;
} AnimSource;

typedef struct {
    u8 pad_000[0x104];
    u8 records[1];
} LinkedAnimSet;

typedef struct {
    u32 flags;
    int blended;
    u8 pad_008[0x11c - 0x008];
    u8 baseAnims[0x148 - 0x11c];
    u8 moveAnims[0x174 - 0x148];
    u8 walkAnims[0x1a0 - 0x174];
    u8 runAnims[0x1f8 - 0x1a0];
    u8 extraAnims[0x21c - 0x1f8];
    u8 records[0x228 - 0x21c];
    LinkedAnimSet *linked;
    u8 pad_22c[0x230 - 0x22c];
} AnimSlot;

typedef struct {
    u8 pad_000[0xa51];
    s8 entryIndex;
    u8 pad_a52[0xb68 - 0xa52];
    AnimSlot slots[1];
    u8 pad_d98[0x1078 - 0xd98];
    AnimSource *source;
} AnimActor;

extern BOOL func_ov001_0206e31c(void);
extern s32 func_ov001_02063a38(void);
extern void *func_ov040_020be03c(void);
extern void *FindSlotRecordById(void *table, int id, int *outIndex);
extern void func_ov021_020a9b94(AnimSlot *slot, void *anims, int index, void *blend, int frame);

void SelectSlotAnimation(AnimActor *actor, int slotIndex, int type, int frame)
{
    void *anims = NULL;
    void *blend = NULL;
    AnimSlot *slot = &actor->slots[slotIndex];
    int index;
    AnimSource *source;
    AnimEntry *entry;

    if (!(slot->flags & 1)) {
        return;
    }
    slot->blended = 0;
    slot->flags &= ~0x400;
    if (type < 0xb) {
        anims = slot->baseAnims;
        index = type;
    } else if (type >= 0xb && type < 0xd) {
        anims = slot->extraAnims;
        index = type - 0xb;
    }
    if (type >= 0xd && type < 0x15) {
        anims = slot->moveAnims;
        index = type - 0xd;
    } else if (type >= 0x15 && type < 0x17) {
        anims = slot->baseAnims;
        index = type - 0xa;
    } else if (type >= 0x17 && type < 0x1a) {
        anims = !func_ov001_0206e31c() ? slot->walkAnims : slot->runAnims;
        index = type - 0x17;
    } else if ((type >= 0x1e && type < 0x2c) || (type >= 0x43 && type < 0x5f)) {
        source = actor->source;
        if (source == NULL) {
            if (func_ov001_02063a38() == 6) {
                index = 0;
                anims = func_ov040_020be03c();
            }
        } else {
            switch (source->type) {
            case 1:
            case 2:
                if (source->count <= 0) {
                    break;
                }
                entry = source->entries[0];
                if (type == 0x20) {
                    entry = source->entries[1];
                }
                anims = entry->anim + 8;
                index = 0;
                break;
            case 3:
                if (source->count <= 0) {
                    break;
                }
                entry = source->entries[actor->entryIndex];
                anims = entry->anim + 8;
                if (entry->blendAnim != NULL) {
                    blend = entry->blendAnim + 8;
                }
                slot->blended = 1;
                index = 0;
                break;
            case 4:
                if (source->kind == 0xc6) {
                    if (source->count <= 0) {
                        break;
                    }
                    entry = source->entries[actor->entryIndex];
                    anims = entry->anim + 8;
                    if (entry->blendAnim != NULL) {
                        blend = entry->blendAnim + 8;
                    }
                    slot->blended = 1;
                    index = 0;
                    break;
                }
                if (source->count <= 0) {
                    break;
                }
                entry = source->entries[0];
                if (entry != NULL) {
                    anims = entry->anim + 8;
                    if (entry->blendAnim != NULL) {
                        blend = entry->blendAnim + 8;
                    }
                    slot->blended = 1;
                }
                index = 0;
                break;            default:
                if (source->count <= 0) {
                    break;
                }
                entry = source->entries[0];
                if (entry != NULL) {
                    anims = entry->anim + 8;
                    if (entry->blendAnim != NULL) {
                        blend = entry->blendAnim + 8;
                    }
                    slot->blended = 1;
                }
                index = 0;
                break;
            }
        }
    } else if (type >= 0x2d && type < 0x43) {
        index = 0;
        anims = FindSlotRecordById(slot->records, type - 0x2d, NULL);
        if (slot->linked != NULL) {
            blend = FindSlotRecordById(slot->linked->records, type - 0x2d, NULL);
        }
        slot->blended = 1;
    }
    func_ov021_020a9b94(slot, anims, index, blend, frame);
}
