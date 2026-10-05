#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x2c];
    s16 pendingSkip;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern void func_ov035_020bad28(void);
extern void ClearSessionPackedBit(int messageId);

int FinishMovieSkip(void)
{
    MovieContext *context = data_ov035_020bc500;

    func_ov035_020bad28();
    if (context->pendingSkip > 0) {
        context->pendingSkip = 0;
        ClearSessionPackedBit(0x3533);
    }
    data_ov035_020bc500->flags |= 0x8000;
    return 6;
}