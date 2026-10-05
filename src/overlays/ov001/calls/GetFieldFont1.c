#include "nitro/types.h"

typedef struct {
    void *resource;
    void *splitCallback;
    u32 unk_08;
} FieldFont;

typedef struct {
    u8 pad_00[0x78];
    FieldFont fonts[4];
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

FieldFont *GetFieldFont1(void)
{
    return &data_ov001_020a04c4.manager->fonts[1];
}
