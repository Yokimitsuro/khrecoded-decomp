#include "nitro/types.h"

extern void *FindLoadedElementById(void *list, u16 id);
extern void SetTagRecordArmed(void *tracker, void *record, BOOL arm);

void DisarmTagById(void *tracker, int id)
{
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, id), FALSE);
}

