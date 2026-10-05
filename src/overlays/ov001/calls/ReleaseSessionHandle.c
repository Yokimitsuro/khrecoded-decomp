#include "nitro/types.h"

typedef struct Session {
    u8 pad_00[0x20];
    u32 flags;
    s32 activeHandle;
} Session;

extern BOOL TryReleaseTaskById(s32 handle);
extern void DeactivateTaskById(s32 handle);
extern void func_ov001_020690c8(void);
extern void func_ov001_02068e44(void);

void ReleaseSessionHandle(Session *session, BOOL flush) {
    if (session->activeHandle != -1 && TryReleaseTaskById(session->activeHandle) == 0) {
        DeactivateTaskById(session->activeHandle);
    }
    if (flush) {
        func_ov001_020690c8();
        func_ov001_02068e44();
    }
    session->flags &= ~0x10;
    session->activeHandle = -1;
}
