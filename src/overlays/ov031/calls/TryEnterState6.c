#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_020645c8(u32 id);
extern void ResumeTaskAndClearFlags(void);
extern void UpdateEventObjects(void);
extern void func_ov001_0206e444(u32 a);
extern void func_ov001_0207d148(u32 a);
extern void func_ov001_0207ef68(u32 a);
extern void func_ov001_02082888(void);
extern void func_ov001_02087650(u32 a);
extern void ForwardToActiveService_02088074(void);
extern void func_ov021_020af59c(u32 a, u32 b);
extern void CacheSeqArcStatus(u32 index);

u32 TryEnterState6(void)
{
    u32 result;
    OverlayState *ctx;

    ctx = data_ov031_020bc820;
    func_ov001_0207d148(7);
    func_ov021_020af59c(1, 0);
    func_ov001_0207ef68(0);
    ResumeTaskAndClearFlags();
    func_ov001_02087650(0);
    result = func_ov001_020645c8(0x3309);
    if (result == 0 && ctx->mode != 3) {
        func_ov001_0206e444(0);
    }
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0xc;
    if (ctx->mode == 0) {
        ctx->flags = ctx->flags & 0xffdf;
    }
    func_ov001_02082888();
    result = func_ov001_020645c8(0x360c);
    if (result == 0) {
        UpdateEventObjects();
        ForwardToActiveService_02088074();
    }
    CacheSeqArcStatus(2);
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 6;
}
