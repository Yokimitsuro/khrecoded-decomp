#ifndef OV021_SHARED_OBJECT_RECORD_H
#define OV021_SHARED_OBJECT_RECORD_H

#include "nitro/types.h"

typedef struct SharedObjectRecord {
    u8 unknown_00[2];
    u16 field_02;
    u8 unknown_04[8];
    u16 flagsA;
    u16 flagsB;
    u16 id;
    s16 mode;
} SharedObjectRecord;

#endif
