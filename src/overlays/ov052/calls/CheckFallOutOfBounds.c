#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*StateCallback)(int entity, int state);

extern VecFx32 *func_ov052_020ceb74(int entity);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL CheckCarriedActorEscape(int entity);
extern void Obj_SetPosition(void *object, const VecFx32 *position);

void CheckFallOutOfBounds(int entity)
{
    VecFx32 *position = func_ov052_020ceb74(entity);
    VecFx32 target;
    if (func_ov001_02063a38() == 4) {
        CheckCarriedActorEscape(entity);
        return;
    }
    if (!func_ov001_020645c8(0x3632) && func_ov052_020ceb74(entity)->y <= -0x3000) {
        target = *position;
        target.y = 0x14000;
        Obj_SetPosition(*(void **)(entity + 0x230), &target);
        (*(StateCallback *)(entity + 0x10ec))(entity, 4);
    }
}
