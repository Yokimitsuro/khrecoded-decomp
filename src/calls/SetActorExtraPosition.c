#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} FxPair;

typedef struct {
    u8 pad_00[0x174];
    FxPair pos;
} ActorExtra;

extern ActorExtra *func_02036254(u32 id);

void SetActorExtraPosition(u32 id, fx32 x, fx32 y) {
    ActorExtra *obj = func_02036254(id);
    FxPair pos = { x, y };
    obj->pos = pos;
}
