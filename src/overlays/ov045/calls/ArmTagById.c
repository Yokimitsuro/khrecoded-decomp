#include "nitro/types.h"

extern void *func_ov027_020b83b0(void *list, u16 id);
extern void func_ov027_020b8408(void *tracker, void *record, BOOL arm);
extern void func_ov027_020b847c(void *tracker, void *record);

void ArmTagById(void *tracker, int id)
{
    void *record = func_ov027_020b83b0(tracker, id);

    func_ov027_020b8408(tracker, record, TRUE);
    func_ov027_020b847c(tracker, record);
}

