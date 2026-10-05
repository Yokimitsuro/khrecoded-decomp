#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventGroup {
    u8 unknown_00[4];
    u8 pending;
    u8 unknown_05[0x17];
} EventGroup;

typedef struct SceneWork {
    u8 unknown_00[0x1f];
    u8 objectGroup;
    u8 objectIndex;
    u8 unknown_21[0x0f];
    s16 targetEventId;
    u8 unknown_32[0x11];
    s8 eventArea;
    u8 unknown_44[0x0c];
    EventGroup *groups;
} SceneWork;

typedef struct EventActor {
    u8 unknown_00[0x38];
    VecFx32 position;
} EventActor;

typedef struct EffectParams {
    VecFx32 *position;
    VecFx32 *offset;
    fx32 scale;
    u16 enable;
    u16 priority;
    int flags;
    u8 unknown_14[0x4c];
} EffectParams;

typedef struct EffectResult {
    u8 unknown_00[0x2c];
    fx32 scale;
} EffectResult;

extern SceneWork *data_ov035_020bc500;
extern const VecFx32 data_ov035_020bc400;
extern int func_ov001_020645c8(int flagId);
extern void func_ov001_020645dc(int flagId);
extern EventActor *func_ov001_0208724c(int area, int eventId);
extern void *func_ov001_0207f060(u32 group, u32 index);
extern int GetActorRegistry(void);
extern EffectResult *func_020351cc(int handle, EffectParams *params);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern void CallFieldObjectHook24(void *object, VecFx32 *position);
extern void func_ov001_0207f71c(void *object, BOOL enabled);
extern void func_ov001_02078680(void);

void OnGroupEventFinished(int group, int eventId) {
    SceneWork *work = data_ov035_020bc500;
    EventActor *actor;
    void *object;
    EffectParams params;
    VecFx32 result;
    VecFx32 offset;
    VecFx32 position;

    work->groups[group].pending--;
    if (func_ov001_020645c8(0x3702) == 0 && eventId == work->targetEventId) {
        actor = func_ov001_0208724c(work->eventArea, eventId);
        object = func_ov001_0207f060(work->objectGroup, work->objectIndex);
        offset = data_ov035_020bc400;
        position = actor->position;
        position.y += 0x800;
        params.scale = 0x1000;
        params.position = &position;
        params.offset = &offset;
        params.enable = 1;
        params.priority = 0xf;
        params.flags = 0;
        AddScaledVector(func_020351cc(GetActorRegistry(), &params)->scale, &offset, &position, &result);
        CallFieldObjectHook24(object, &result);
        func_ov001_0207f71c(object, TRUE);
        func_ov001_020645dc(0x3702);
    }
    func_ov001_02078680();
}
