#include "nitro/types.h"

extern void *func_ov027_020b83b0(void *list, u16 id);
extern void func_ov027_020b8408(void *tracker, void *record, BOOL arm);

void DisarmTagById(void *tracker, int id)
{
    func_ov027_020b8408(tracker, func_ov027_020b83b0(tracker, id), FALSE);
}

