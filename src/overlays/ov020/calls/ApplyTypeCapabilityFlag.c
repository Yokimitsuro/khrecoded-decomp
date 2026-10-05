#include "nitro/types.h"

extern BOOL ActorSlot_IsFlag8SetByIndex(u8 typeId);
extern void CacheEntry_SetActive(int self, BOOL flag);

void ApplyTypeCapabilityFlag(int self) {
    BOOL flag = ActorSlot_IsFlag8SetByIndex(*(u8 *)(self + 0x32));
    CacheEntry_SetActive(self, flag);
}
