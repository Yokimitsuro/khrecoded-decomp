#include "nitro/types.h"

extern void *FindLoadedElementById(void *list, u16 id);
extern void SetTagRecordArmed(void *tracker, void *record, BOOL arm);
extern void func_ov027_020b847c(void *tracker, void *record);

void ArmTagById(void *tracker, int id)
{
    void *record = FindLoadedElementById(tracker, id);

    SetTagRecordArmed(tracker, record, TRUE);
    func_ov027_020b847c(tracker, record);
}

