#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    u8 pad_00[0x10];
    fx32 height;
} ShapeData;

typedef struct ActorBody {
    u8 pad_000[0x130];
    ShapeData *shape;
    s32 bounds[6];
    s32 shapeKind;
    VecFx32 delta;
    s32 sweptBounds[6];
} ActorBody;

typedef struct ObjectDef {
    u8 pad_00[0x5a];
    u8 kind;
} ObjectDef;

typedef struct FieldObject {
    struct FieldObject *next;
    ObjectDef *def;
    u8 pad_08[0x2a];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[8];
    s8 linkIndex;
    s8 linkGroup;
    u8 pad_4e[2];
    u16 flags;
    u8 pad_52[0x12];
    VecFx32 velocity;
    u8 pad_70[0x24];
    VecFx32 anchor;
    s32 kind;
    s32 areaId;
    u8 pad_a8[0xc];
    s32 spawnParam;
    u8 level;
} FieldObject;

extern ActorBody *ActorRegistry_GetEntityByIndex(u32 id);
extern int func_ov031_020bc758(void);
extern void SetShapePosition(void *shape, const VecFx32 *position);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL func_ov031_020bc5b4(fx32 value, fx32 range);
extern void func_ov018_020a335c(FieldObject *obj, BOOL disable);
extern BOOL func_ov031_020bc670(int area);
extern BOOL func_ov018_020a3490(FieldObject *obj);
extern fx32 func_ov031_020bc6ac(fx32 scale);
extern FieldObject *func_ov001_02087264(void);
extern void func_ov018_020a35d8(FieldObject *obj, VecFx32 *position, int spawnParam, u8 level, int kind, s8 linkIndex, s8 linkGroup, int flag);

int FieldObject_ShiftWithArea(FieldObject *obj, VecFx32 *move, int area)
{
    ActorBody *body;
    FieldObject *other;
    VecFx32 center;
    VecFx32 spawnPos;
    VecFx32 delta;
    int level;

    if (obj->flags & 8) {
        return 0;
    }
    body = ActorRegistry_GetEntityByIndex(obj->actorId);
    if (obj->areaId == func_ov031_020bc758()) {
        return 0;
    }
    center = obj->position;
    center.y += body->shape->height;
    SetShapePosition(&body->shape, &center);
    OffsetBoxByDelta(body->bounds, body->sweptBounds, &body->delta);
    func_01ff9e0c(&obj->position, move, &obj->position);
    func_01ff9e0c(&obj->anchor, move, &obj->anchor);
    if (func_ov031_020bc5b4(obj->anchor.z, 0x1000)) {
        if (!(obj->flags & 0x400)) {
            func_ov018_020a335c(obj, TRUE);
        }
        if (obj->flags & 0x1000) {
            return 0;
        }
        if (obj->flags & 0x400) {
            obj->flags |= 0x1000;
        }
        if (!(obj->flags & 0x100) && func_ov031_020bc670(area) &&
            (area != 0 || !func_ov018_020a3490(obj))) {
            spawnPos = obj->anchor;
            spawnPos.z += func_ov031_020bc6ac(0x1000);
            for (other = func_ov001_02087264(); other != NULL; other = other->next) {
                if (other->def->kind == 6 && (other->flags & 8)) {
                    level = (obj->level != 0xff) ? obj->level - 1 : 0xff;
                    func_ov018_020a35d8(other, &spawnPos, obj->spawnParam, level, obj->kind, obj->linkIndex, obj->linkGroup, 1);
                    other->flags |= 0x200;
                    break;
                }
            }
        }
    } else {
        func_01ff9e0c(move, &obj->velocity, &delta);
        body->delta = delta;
        OffsetBoxByDelta(body->bounds, body->sweptBounds, &body->delta);
    }
    return 0;
}
