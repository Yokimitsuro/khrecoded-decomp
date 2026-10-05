#include "nitro/types.h"

typedef struct TouchHandler {
    u32 words[5];
} TouchHandler;

typedef struct FieldObjectWork {
    u8 pad_000[0x494];
    s32 interactRange;
} FieldObjectWork;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldObjectWork *work;
    u8 pad_0c[0x5c];
    void (*onTouchStart)(struct FieldObject *object);
    void (*onTouchEnd)(struct FieldObject *object);
    s32 touchState;
    TouchHandler *touchHandler;
} FieldObject;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern TouchHandler MakeCommandRecord(void (*callback)(FieldObject *), FieldObject *owner, int mode, int flags);
extern void func_ov001_02085d74(FieldObject *object);
extern void func_ov001_02085d84(FieldObject *object);
extern void ScrollObjectAndFade(FieldObject *object);

void AttachTouchHandler(FieldObject *object)
{
    object->work->interactRange = 0x1800;
    if (object->touchHandler == NULL) {
        object->touchHandler = NNSi_FndAllocFromDefaultHeap(sizeof(TouchHandler));
    }
    object->onTouchStart = func_ov001_02085d74;
    object->onTouchEnd = func_ov001_02085d84;
    object->touchState = 0;
    *object->touchHandler = MakeCommandRecord(ScrollObjectAndFade, object, 2, 0);
}
