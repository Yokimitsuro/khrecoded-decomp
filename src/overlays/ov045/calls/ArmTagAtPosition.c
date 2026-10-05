#include "nitro/types.h"

extern void *FindLoadedElementById(void *list, u16 id);
extern void PositionListRecords(void *container, void *list, s16 position);
extern void func_ov027_020b8408(void *tracker, void *record, BOOL arm);
extern void func_ov027_020b847c(void *tracker, void *record);

void ArmTagAtPosition(void *tracker, int id, int position)
{
    void *record = FindLoadedElementById(tracker, id);

    PositionListRecords(tracker, record, position);
    func_ov027_020b8408(tracker, record, TRUE);
    func_ov027_020b847c(tracker, record);
}
