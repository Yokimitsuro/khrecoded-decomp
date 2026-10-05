#include "nitro/types.h"

typedef struct {
    u8 reserved[0x1348];
    s32 (*commandHandler)(u16 pressed);
} FieldManager;

typedef struct {
    u32 reserved;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

s32 CallFieldCommandHandler(u16 pressed)
{
    if (data_ov001_020a04c4.manager->commandHandler == NULL) {
        return 5;
    }
    return data_ov001_020a04c4.manager->commandHandler(pressed);
}
