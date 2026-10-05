#include "nitro/types.h"

typedef struct LayerConfig {
    void *initialEntry;
    int mode;
    int value;
    int count;
} LayerConfig;

typedef struct LayerObject {
    u8 pad_0000[0x4604];
    int mode;
    int format;
    int value;
    u16 cursor;
    u16 pad_4612;
    u16 count;
    u16 remaining;
    u8 pad_4618[0x601c - 0x4618];
    int enabled;
    int pad_6020;
    int width;
    int height;
} LayerObject;

extern int func_0204e860(LayerObject *object, void *entrySource);

BOOL ConfigureImageEntryList(LayerObject *object, const LayerConfig *config)
{
    int mode = config->mode;

    object->mode = mode;
    switch (mode) {
    case 1:
        object->format = 0x12;
        break;
    case 2:
        object->format = 0x22;
        break;
    }
    object->enabled = 1;
    object->width = 0x10;
    object->height = 0x80;
    object->value = config->value;
    object->count = config->count;
    object->remaining = object->count;
    object->cursor = 0;
    if (config->initialEntry != NULL) {
        func_0204e860(object, config->initialEntry);
    }
    return TRUE;
}
