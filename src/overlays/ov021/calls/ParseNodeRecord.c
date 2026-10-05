#include "nitro/types.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 unk_12;
    u8 value : 5;
    u8 enabled : 1;
} NodeEntryKind0;

typedef struct {
    u8 unk_00;
    u8 pad_01[3];
    s32 unk_04;
    u8 unk_08;
    u8 unk_09;
} NodeEntryKind1;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[2];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
} NodeEntryKind2;

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s8 unk_20;
    s8 unk_21;
    u8 kind : 3;
    u8 flag : 1;
    s8 unk_23;
    union {
        NodeEntryKind0 kind0;
        NodeEntryKind1 kind1;
        NodeEntryKind2 kind2;
    } u;
    u8 pad_40[0x14];
} NodeEntry;

typedef struct {
    s16 id;
    u8 group;
    u8 pad_03;
    s32 unk_04;
    s32 params[2][4];
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s16 unk_40;
    s16 entryCount;
    NodeEntry *entries;
} NodeRecord;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void ResetModelGroup(NodeRecord *node);

void ParseNodeRecord(NodeRecord *node, u8 layer, s32 *src)
{
    s32 *row;
    int i;
    int j;
    NodeEntry *entry;

    node->id = src[0];
    node->group = src[1];
    node->unk_04 = src[2];
    src += 3;
    for (i = 0; i < 2; i++) {
        row = node->params[i];
        for (j = 0; j < 4; j++) {
            row[j] = *src++;
        }
    }
    node->unk_28 = src[0];
    node->unk_2C = src[1];
    node->unk_40 = src[2];
    node->unk_30 = src[3];
    node->unk_34 = src[4];
    node->unk_38 = src[5];
    node->unk_3C = src[6];
    node->entryCount = src[7];
    node->entries = NULL;
    src += 8;
    if (node->entryCount > 0) {
        node->entries = NNSi_FndAllocFromDefaultHeap(node->entryCount * sizeof(NodeEntry));
    }
    for (i = 0; i < node->entryCount; i++) {
        entry = &node->entries[i];
        entry->unk_00 = src[0];
        entry->unk_04 = src[1];
        entry->unk_08 = src[2];
        entry->kind = src[3];
        entry->unk_0C = src[4];
        entry->unk_10 = src[5];
        entry->unk_14 = src[6];
        entry->unk_18 = src[7];
        entry->unk_20 = src[8];
        entry->unk_1C = src[9];
        entry->unk_21 = src[10];
        entry->flag = src[11];
        entry->unk_23 = src[12];
        src += 13;
        if (entry->unk_23 >= 4) {
            entry->unk_23 = 3;
        }
        switch (entry->kind) {
        case 0: {
            NodeEntryKind0 *kind0 = &entry->u.kind0;
            kind0->unk_00 = src[0];
            kind0->unk_04 = src[1];
            kind0->unk_08 = src[2];
            kind0->unk_0C = src[3];
            kind0->unk_10 = src[4];
            kind0->unk_12 = src[5];
            kind0->enabled = src[6] != 0;
            kind0->value = src[7];
            src += 8;
            break;
        }
        case 1: {
            NodeEntryKind1 *kind1 = &entry->u.kind1;
            kind1->unk_00 = src[0];
            kind1->unk_04 = src[1];
            kind1->unk_08 = src[2];
            kind1->unk_09 = src[3];
            src += 4;
            break;
        }
        case 2: {
            NodeEntryKind2 *kind2 = &entry->u.kind2;
            kind2->unk_00 = src[0];
            kind2->unk_01 = src[1];
            kind2->unk_04 = src[2];
            kind2->unk_08 = src[3];
            kind2->unk_0C = src[4];
            kind2->unk_10 = src[5];
            kind2->unk_14 = src[6];
            kind2->unk_18 = src[7];
            src += 8;
            break;
        }
        }
    }
    ResetModelGroup(node);
}
