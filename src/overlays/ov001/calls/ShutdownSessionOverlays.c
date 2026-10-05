#include "nitro/types.h"

typedef struct SubOverlayWork {
    u8 pad_00[0x10];
    BOOL (*poll)(void);
    void (*shutdown)(void);
    u8 pad_18[0x18];
} SubOverlayWork;

typedef struct SubOverlaySlot {
    s32 activeId;
    s32 overlayId;
    s8 state;
    u8 pad_09[3];
    SubOverlayWork work;
} SubOverlaySlot;

typedef struct Session {
    u8 pad_0000[0x14];
    s32 overlayId;
    u8 pad_0018;
    s8 overlayState;
    u8 pad_001a[0x2800 - 0x1a];
    SubOverlaySlot subOverlay;
} Session;

extern Session *data_ov001_020a0480;
extern void FlushPendingFieldUpdate(void);
extern void func_02029fac(int processor, int overlayId);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);
extern void ShutdownActorRegistry(void);
extern void InitActorRegistry(void);
extern void func_ov001_020674a0(void);

s32 ShutdownSessionOverlays(void) {
    Session *session = data_ov001_020a0480;
    SubOverlaySlot *slot = &session->subOverlay;

    if (session->subOverlay.state != 1) {
        FlushPendingFieldUpdate();
    }
    if (slot->activeId != -1) {
        slot->work.shutdown();
        if (slot->overlayId != -1) {
            func_02029fac(0, slot->overlayId);
        }
        MIi_CpuClear32(0, &slot->work, sizeof(SubOverlayWork));
        slot->activeId = -1;
    }
    if (session->overlayId != -1) {
        func_02029fac(0, session->overlayId);
        session->overlayId = -1;
        session->overlayState = -1;
    }
    ShutdownActorRegistry();
    InitActorRegistry();
    func_ov001_020674a0();
    return 1;
}
