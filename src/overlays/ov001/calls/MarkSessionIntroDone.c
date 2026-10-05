#include "nitro/types.h"

typedef struct SessionFlags {
    u8 pad_00[0xc];
    u32 unk0 : 15;
    u32 introDone : 1;
    u32 unk16 : 16;
} SessionFlags;

typedef struct Session {
    u8 pad_000[0x208];
    SessionFlags flags;
} Session;

extern Session *data_ov001_020a0480;
extern void func_ov001_02068d78(void);

void MarkSessionIntroDone(void)
{
    SessionFlags *flags = &data_ov001_020a0480->flags;

    if (!flags->introDone) {
        func_ov001_02068d78();
        flags->introDone = 1;
    }
}
