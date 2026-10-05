#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u32 vramBase;
} ScriptScreen;

extern ScriptScreen data_ov021_020b5640;

u32 MakePaletteUploadParams40(u32 index) {
    return 0x80000000 | (((data_ov021_020b5640.vramBase + 0x8000) & 0xfffffc) << 7) | ((index + 0x28) & 0x1ff);
}
