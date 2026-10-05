#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x67];
    u8 activeBit : 1;
    u8 otherFlags : 7;
} FieldObject;

typedef struct Session {
    u8 pad_000[0x214];
    u32 lowFlags : 19;
    u32 flag19 : 1;
    u32 highFlags : 12;
} Session;

extern Session *data_ov001_020a0480;
extern void func_ov001_02063d4c(int parameterId, int value);
extern BOOL func_ov001_0207d484(int enable);
extern void ReleaseOwnerResource(FieldObject *object, int arg);

void FieldObject_ReleaseWithSlotReset(FieldObject *object, int arg)
{
    func_ov001_02063d4c(6, 0x1000);
    object->activeBit = 0;
    func_ov001_0207d484(0);
    data_ov001_020a0480->flag19 = 0;
    ReleaseOwnerResource(object, arg);
}
