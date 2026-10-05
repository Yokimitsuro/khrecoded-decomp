#include "nitro/types.h"

extern u8 *gSoundWork;
extern u8 *GetRecentHistoryEntry(int value);
extern void PushSoundQueueEntry(int kind, int arg1, int arg2);

int SetSelectionIfChanged(int selection)
{
    u8 *record;

    if (*(s16 *)(gSoundWork + 0xb472a) != selection ||
        *(u8 *)(gSoundWork + 0xb47be) == 1) {
        record = GetRecentHistoryEntry(0);
        if (record == NULL || record[0] != 2) {
            PushSoundQueueEntry(2, selection, 0);
        } else {
            record[1] = (u8)selection;
        }
    }
    return 1;
}
