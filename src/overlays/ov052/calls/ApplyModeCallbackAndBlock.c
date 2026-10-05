#include "nitro/types.h"

typedef struct {
    int words[4];
} Block16;

typedef void (*ModeCallback)(int entity, int mode);

void ApplyModeCallbackAndBlock(int entity, int mode, Block16 *block)
{
    if (*(ModeCallback *)(entity + 0x200) != NULL) {
        (*(ModeCallback *)(entity + 0x200))(entity, 0);
    }
    if (mode != 0) {
        if (*(ModeCallback *)(entity + 0x200) != NULL) {
            (*(ModeCallback *)(entity + 0x200))(entity, mode);
        }
        *(Block16 *)(entity + 0x105c) = *block;
    }
}
