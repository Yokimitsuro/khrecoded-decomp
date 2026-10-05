#include "nitro/types.h"

typedef struct SceneRequest {
    char name[0x10];
    u32 param;
} SceneRequest;

typedef struct Session {
    u8 pad_0000[0x20];
    u32 flags;
    u8 pad_0024[0x2808 - 0x24];
    s8 mode;
} Session;

extern Session *data_ov001_020a0480;
extern void StartIdleSceneObjects(void);
extern void NotifyManagerEntryObjects(void);
extern void func_ov001_0206e444(s32 enable);
extern void ForwardSubModeEnd(s32 value);
extern void func_ov001_02087834(void);
extern void func_ov001_020877ec(void);
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern void ActorManager_StartScene(SceneRequest *request);

void StartSessionScene(const char *sceneName) {
    SceneRequest request;
    if (data_ov001_020a0480->mode == 3 || data_ov001_020a0480->mode == 7) {
        request.param = 0;
    } else {
        request.param = 1;
    }
    StartIdleSceneObjects();
    NotifyManagerEntryObjects();
    func_ov001_0206e444(1);
    ForwardSubModeEnd(1);
    func_ov001_02087834();
    func_ov001_020877ec();
    OS_SPrintf(request.name, sceneName);
    ActorManager_StartScene(&request);
    data_ov001_020a0480->flags |= 0x20;
}
