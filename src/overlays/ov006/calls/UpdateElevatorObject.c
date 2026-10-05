#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x84];
    s8 group;
    s8 index;
    u8 pad_86[0xe];
    s8 stopIndex;
    u8 pad_95[3];
    fx32 riseSpeed;
    fx32 fallSpeed;
    fx32 stops[4];
} ElevatorWork;

typedef struct {
    u8 pad_00[8];
    ElevatorWork *work;
} ElevatorObject;

extern void *func_ov001_0207f060(int group, int index);
extern VecFx32 *func_ov001_0207f838(void *object);
extern BOOL func_ov001_020645c8(int bitId);
extern u16 FieldObject_GetSavedValue(ElevatorObject *object);
extern void FieldObject_SetSavedValue(ElevatorObject *object, u16 value);
extern void CallFieldObjectHook24(void *object, VecFx32 *position);

int UpdateElevatorObject(ElevatorObject *object) {
    ElevatorWork *work = object->work;
    VecFx32 position = *func_ov001_0207f838(func_ov001_0207f060(work->group, work->index));
    fx32 distance = work->stops[work->stopIndex] - position.y;

    if (func_ov001_020645c8(0x3717)) {
        return 0;
    }
    if (position.y == 0) {
        return 0;
    }
    if (distance > 0) {
        position.y += work->riseSpeed;
        if (work->stops[work->stopIndex] < position.y) {
            position.y = work->stops[work->stopIndex];
        }
    } else if (distance < 0) {
        position.y -= work->fallSpeed;
        if (position.y < work->stops[work->stopIndex]) {
            position.y = work->stops[work->stopIndex];
        }
    }
    if (position.y <= 0) {
        position.y = 0;
        FieldObject_SetSavedValue(object, FieldObject_GetSavedValue(object) | 2);
    }
    CallFieldObjectHook24(func_ov001_0207f060(work->group, work->index), &position);
    return 0;
}
