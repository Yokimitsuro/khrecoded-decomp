#include "nitro/types.h"

extern BOOL ActorSlot_IsFlag8SetByIndex(u8 typeId);
extern void func_ov001_02087280(int self, BOOL flag);

void ApplyTypeCapabilityFlag(int self) {
    BOOL flag = ActorSlot_IsFlag8SetByIndex(*(u8 *)(self + 0x32));
    func_ov001_02087280(self, flag);
}
