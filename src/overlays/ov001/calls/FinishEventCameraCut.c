#include "nitro/types.h"

typedef struct {
    u32 words[14];
} CameraCutHeader;

typedef struct {
    CameraCutHeader header;
    s32 target;
    s32 focus;
    u8 pad_40[0x8];
} CameraCutParams;

typedef struct {
    CameraCutHeader header;
    u8 pad_38[0x44 - 0x38];
    s32 defaultTarget;
    u8 pad_48[0x80 - 0x48];
    s32 focus;
    u8 pad_84[0x98 - 0x84];
    s32 cutId;
    u8 pad_9c[0x1d4 - 0x9c];
    void *buffer;
    u32 task;
    u16 active;
    u8 pad_1de[0x1e0 - 0x1de];
    s32 targetOverride;
} EventCameraManager;

extern EventCameraManager *data_ov001_020a0514;

extern int ZeroHalfThenFree(void *block);
extern u32 GetManagerUnknownValue(void);
extern void ForwardSubModeValue(CameraCutParams *params);
extern BOOL GetPanelFieldB8(void);
extern void func_ov021_020af6e4(void);
extern void SetSubModeFrozen(BOOL frozen);
extern void func_ov021_020af528(int value);
extern void ResetFieldCamera(void);
extern void Obj_SetWord14(u32 task, void (*callback)(void));
extern void func_ov001_0208b7a4(void);

void FinishEventCameraCut(void) {
    EventCameraManager *manager = data_ov001_020a0514;
    CameraCutParams params;

    if (manager->active == 0) {
        return;
    }
    if (manager->buffer != NULL) {
        ZeroHalfThenFree(manager->buffer);
        manager->buffer = NULL;
    }
    if (GetManagerUnknownValue()) {
        if (manager->cutId != -1) {
            params.header = manager->header;
            if (manager->targetOverride != -1) {
                params.target = manager->targetOverride;
            } else {
                params.target = manager->defaultTarget;
            }
            params.focus = manager->focus;
            ForwardSubModeValue(&params);
        }
        if (GetPanelFieldB8()) {
            func_ov021_020af6e4();
            SetSubModeFrozen(FALSE);
            func_ov021_020af528(0);
        }
    }
    ResetFieldCamera();
    manager->active = 0;
    Obj_SetWord14(manager->task, func_ov001_0208b7a4);
}
