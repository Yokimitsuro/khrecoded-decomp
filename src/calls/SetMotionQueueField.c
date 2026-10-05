#include "nitro/types.h"

typedef struct GlobalMotionQueue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
    u8 pad_14[0x18];
    s32 unk_2c;
} GlobalMotionQueue;

typedef struct FieldWriteRequest {
    s32 value;
    s32 field;
} FieldWriteRequest;

extern GlobalMotionQueue data_027e0134;

void SetMotionQueueField(FieldWriteRequest *request) {
    switch (request->field) {
    case 1:
        data_027e0134.unk_04 = request->value;
        return;
    case 2:
        data_027e0134.unk_08 = request->value;
        return;
    case 3:
        data_027e0134.unk_0c = request->value;
        return;
    case 4:
        data_027e0134.unk_10 = request->value;
        return;
    default:
        return;
    }
}
