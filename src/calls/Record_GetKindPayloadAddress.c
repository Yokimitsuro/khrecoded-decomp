#include "nitro/types.h"

typedef struct {
    s32 base;
    s32 kind;
} Record;

s32 Record_GetKindPayloadAddress(Record *rec)
{
    switch (rec->kind) {
    case 0:
        break;
    case 1:
        return rec->base + 0x80;
    case 2:
        return rec->base + 0x80;
    case 3:
        return rec->base + 0x80;
    case 4:
        return rec->base + 0x10;
    }
    return 0;
}
