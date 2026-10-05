#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x26];
    s8 layoutOffset;
} SceneContext;

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0080;
extern void func_ov001_0207d148(s32 value);
extern void func_ov001_0207d238(s32 value);
extern void ApplyVerticalLayoutOffset(BOOL raised);
extern void func_ov001_0207d3ac(s32 value);
extern s32 func_ov001_02063a6c(void);
extern void func_ov021_020af59c(s32 value, s32 flag);
extern void func_ov001_0207ef68(s32 value);
extern void ResumeTaskAndClearFlags(void);
extern void SetMenuHighlight(s32 value);
extern void func_ov001_02087650(int enable);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_0206e444(s32 value);
extern void UpdateEventObjects(void);
extern void ForwardToActiveService_02088074(void);
extern int CacheSeqArcStatus(int index);

s32 ResumeSceneAndAdvance(void) {
    SceneState *scene = data_ov032_020c0080.scene;
    func_ov001_0207d148(1);
    func_ov001_0207d148(0x41);
    func_ov001_0207d238(1);
    ApplyVerticalLayoutOffset(data_ov032_020c0080.context->layoutOffset >= 0);
    func_ov001_0207d3ac(1);
    func_ov021_020af59c(func_ov001_02063a6c(), 0);
    func_ov001_0207ef68(0);
    ResumeTaskAndClearFlags();
    SetMenuHighlight(0);
    func_ov001_02087650(0);
    if (!func_ov001_020645c8(0x3309) && scene->mode != 3) {
        func_ov001_0206e444(0);
    }
    data_ov032_020c0080.scene->flags |= 0xc;
    if (scene->mode < 0 || scene->mode == 3) {
        scene->flags &= 0xffdf;
    }
    if (!func_ov001_020645c8(0x360c)) {
        UpdateEventObjects();
        ForwardToActiveService_02088074();
    }
    CacheSeqArcStatus(2);
    data_ov032_020c0080.scene->flags |= 0x8000;
    return 6;
}
