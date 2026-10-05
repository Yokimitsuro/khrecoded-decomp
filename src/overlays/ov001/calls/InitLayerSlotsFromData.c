#include "nitro/types.h"

typedef struct {
    u8 unk0;
    u8 kind : 4;
    u8 enabled : 1;
    u8 unk1_5 : 3;
    u8 pad[6];
} LayerDef;

typedef struct {
    u16 unk0;
    u16 count;
    u8 pad_04[0x20];
    LayerDef *defs;
} LayerSet;

typedef struct {
    u8 pad_00[8];
    LayerSet *sets[1];
} LayerSetTable;

typedef struct {
    u8 pad_000[0x104];
    u8 flags;
    u8 unk105;
    u8 kind;
    u8 unk107;
} LayerSlot;

typedef struct {
    LayerSetTable *table;
    u8 pad_04[9];
    s8 setIndex;
    u8 pad_0e[10];
    LayerSlot slots[16];
} LayerContext;

extern LayerContext *data_ov001_020a048c;
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);

void InitLayerSlotsFromData(void)
{
    LayerContext *ctx = data_ov001_020a048c;
    int i = 0;
    LayerSet *set = ctx->table->sets[ctx->setIndex];

    MIi_CpuClearFast(0, ctx->slots, sizeof(ctx->slots));
    for (; i < set->count; i++) {
        LayerSlot *slot = &ctx->slots[i];
        LayerDef *def = &set->defs[i];
        slot->kind = def->kind;
        if (def->enabled) {
            slot->flags |= 1;
        }
    }
}
