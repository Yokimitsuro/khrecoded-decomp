#include "nitro/types.h"

typedef struct SlotMenuWork {
    u8 pad_00000[0x49854];
    u8 bgPriority;
} SlotMenuWork;

void SlotMenu_SetBg0Priority(SlotMenuWork *work, u16 priority)
{
    *(vu16 *)0x04000008 = (u16)((*(vu16 *)0x04000008 & ~3) | priority);
    work->bgPriority = priority;
}
