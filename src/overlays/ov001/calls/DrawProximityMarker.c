#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x78];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 position;
    fx32 scaleX;
    fx32 pad_b4;
    fx32 scaleZ;
} MarkerNode;

typedef struct {
    u8 pad_00[0xc];
    MarkerNode node;
} MarkerRecord;

typedef struct {
    u8 pad_000[8];
    u16 flags;
    u8 pad_00a[0x286];
    fx32 baseY;
    u8 pad_294[0x1c];
    fx32 size;
    u8 pad_2b4[0xc];
    VecFx32 position;
    u8 pad_2cc[0x50];
    fx32 scale;
    u8 pad_320[0x10];
    fx32 range;
} MarkerOwner;

extern void func_ov001_020995ec(int kind, int owner);
extern MarkerRecord *func_ov001_0209c0c8(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int id);
extern void func_01ffb12c(MarkerNode *node);

void DrawProximityMarker(MarkerOwner *owner)
{
    MarkerNode *node;
    fx32 distance;
    fx32 ratio;
    fx32 scale;
    int alpha;
    int mode;

    func_ov001_020995ec(0x1c, 1);
    node = &func_ov001_0209c0c8()->node;
    if (!(owner->flags & 0x10)) {
        return;
    }
    distance = owner->position.y - owner->baseY;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0) {
        distance = -distance;
    }
    if (distance >= owner->range || owner->size <= 0) {
        return;
    }
    ratio = FX_Div(distance, owner->range);
    if (ratio > 0x1000) {
        ratio = 0x1000;
    }
    scale = FX_Mul(FX_Mul(owner->size, owner->scale), 0x1000 - ratio);
    node->position = owner->position;
    node->position.y = owner->baseY + 0x29 + FX_Mul(owner->size, 0x7b);
    node->scaleX = scale;
    node->scaleZ = scale;
    alpha = 8 - ((ratio * 8) >> 12);
    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    if (mode == 7) {
        alpha = 0x1f;
    }
    NNS_G3dMdlSetMdlAlphaAll(node->model, alpha);
    NNS_G3dMdlSetMdlPolygonIDAll(node->model, 0x3f);
    func_01ffb12c(node);
}
