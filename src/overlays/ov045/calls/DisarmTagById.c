#include "nitro/types.h"

extern void *FindLoadedElementById(void *list, u16 id);
extern void func_ov027_020b8408(void *tracker, void *record, BOOL arm);

void DisarmTagById(void *tracker, int id)
{
    func_ov027_020b8408(tracker, FindLoadedElementById(tracker, id), FALSE);
}

