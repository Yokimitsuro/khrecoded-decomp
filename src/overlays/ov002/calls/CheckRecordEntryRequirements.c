#include "nitro/types.h"

extern u32 AcquireRecordSlot();
extern u32 GetRecordTableCEntry();
extern u32 ReleaseRecordSlot();
extern u32 IsRecordFlagBitSet();

BOOL CheckRecordEntryRequirements(int context)

{
  short entryId;
  short *entries;
  int status;
  int index;
  
  AcquireRecordSlot(10,1);
  entries = (short *)(GetRecordTableCEntry(context) + 6);
  index = 0;
  do {
    entryId = entries[index];
    if (((-1 < entryId) && (entryId < 0x5a1)) && (status = IsRecordFlagBitSet(entryId), status <= 0)) break;
    index = index + 1;
  } while (index < 0x14);
  ReleaseRecordSlot(10);
  return index >= 0x14;
}
