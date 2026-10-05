#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void code();

extern void ApplyTimeScaledSpeed(int entity, fx32 targetSpeed);
extern void func_ov052_020c9854(int entity);
extern void ApplyActorVelocity(int entity);
extern fx32 func_ov001_0206db44(void);
extern void func_ov052_020c969c(int entity);
extern void func_ov052_020c97c4(int entity);
extern void func_ov021_020a7fc4(int subObject, s32 a, s32 b);

/* Runs the actor's per-update subsystem refresh */
void RefreshActorState(int entity)
{
    fx32 timeScale;

    ApplyTimeScaledSpeed(entity, *(fx32 *)(entity + 0x9f4));
    func_ov052_020c9854(entity);
    ApplyActorVelocity(entity);
    timeScale = func_ov001_0206db44();
    if (*(code **)(entity + 0x1ec) != (code *)0) {
        (**(code **)(entity + 0x1ec))(entity, timeScale);
    }
    func_ov052_020c969c(entity);
    (**(code **)(entity + 0x9bc))(entity);
    func_ov052_020c97c4(entity);
    func_ov021_020a7fc4(entity + 0xb2c, *(s32 *)(entity + 0x75c), *(s32 *)(entity + 0x760));
}
