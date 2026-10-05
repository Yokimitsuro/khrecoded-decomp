#include "nitro/types.h"

typedef struct {
    s32 base;
    s32 kind;
} Record;

extern s32 Record_GetKindPayloadAddress(Record *rec);
extern u8 *GetWorldMeshNamedEntry(u8 id);
extern u8 *GetWorldNamedEntry(u8 id);
extern BOOL func_ov001_020681e8(u8 *entry, u32 kind);

/* Checks the record's entries for a matching kind. */
s32 ContainsMatchingEntry(Record *self, u32 kind) {
    u8 *base = (u8 *)Record_GetKindPayloadAddress(self);
    switch (self->kind) {
    case 0:
        break;
    case 1: {
        u32 i = 0;
        do {
            u8 *entry = GetWorldMeshNamedEntry(base[i]);
            if (func_ov001_020681e8(entry, kind) != 0) {
                return 1;
            }
            i = (i + 1) & 0xff;
        } while (i < 3);
        break;
    }
    case 2:
        goto shared;
    case 3:
    shared: {
        u32 i = 0;
        do {
            u8 *entry = GetWorldMeshNamedEntry(base[i]);
            if (func_ov001_020681e8(entry, kind) != 0) {
                return 1;
            }
            i = (i + 1) & 0xff;
        } while (i < 4);
        break;
    }
    case 4: {
        u32 i = 0;
        do {
            u8 *entry = GetWorldNamedEntry(base[i]);
            if (func_ov001_020681e8(entry, kind) != 0) {
                return 1;
            }
            i = (i + 1) & 0xff;
        } while (i < 3);
        break;
    }
    }
    return 0;
}
