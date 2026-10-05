#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov038_020bd160;
extern void StoreToGlobalPtr4Field28(s32 value);
extern void func_ov038_020bbcbc(void);

u32 EnableOv038SoundCtx(void)
{
    func_ov038_020bbcbc();
    if ((data_ov038_020bd160->flags & 1) != 0) {
        data_ov038_020bd160->flags = data_ov038_020bd160->flags & 0xfffe;
    }
    StoreToGlobalPtr4Field28(0);
    return 2;
}
