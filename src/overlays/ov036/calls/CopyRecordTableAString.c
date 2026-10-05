#include "nitro/types.h"

extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern void AcquireRecordSlot(s32 id, s32 value);
extern void ReleaseRecordSlot(s32 id);
extern int GetRecordSlotPair0Entry(s32 id);
extern unsigned short *Utf16Copy(unsigned short *destination, unsigned short *source);

void CopyRecordTableAString(s32 id, unsigned short *destination)
{
    int entry;

    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    entry = GetRecordSlotPair0Entry(id);
    Utf16Copy(destination, *(unsigned short **)(entry + 0x40));
    ReleaseRecordSlot(0);
    ReleaseRecordManager();
}
