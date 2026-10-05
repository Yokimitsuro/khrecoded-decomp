#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x10];
    u8 tagTracker[0x4c];
    u8 objects[0x6b04];
    u8 text[0xa4];
    int counters[8][10];
    int badgeEntry;
    int rowEntries[6];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen data_ov034_020c0fa0;

extern void *FindWidgetById(void *objects, int id);
extern void SetEntrySlotsVisible(void *objects, void *object, int visible);
extern void CallVirtualHandlerSlot1(void *text, int arg);
extern void Text_UploadTileBuffer(void *text);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern void IndexedRecords_SetFlag2(void *objects, int slotIndex, int enabled);
extern void func_0204f0d4(void *objects, int slotIndex);

#define WORK (data_ov034_020c0fa0.work)

void ResetResultsObjects(void)
{
    int i;
    int row;
    void *object;

    for (i = 0; i <= 0xe6; i++) {
        object = FindWidgetById(WORK->objects, i);
        if (object != NULL) {
            SetEntrySlotsVisible(WORK->objects, object, 0);
        }
    }
    CallVirtualHandlerSlot1(WORK->text, 0);
    Text_UploadTileBuffer(WORK->text);
    for (i = 0; i < 7; i++) {
        func_ov027_020b8288(WORK->tagTracker, FindActiveRecordById(WORK->tagTracker, i));
    }
    IndexedRecords_SetFlag2(WORK->objects, WORK->badgeEntry, 0);
    for (i = 0; i < 6; i++) {
        IndexedRecords_SetFlag2(WORK->objects, WORK->rowEntries[i], 0);
    }
    for (row = 0; row < 8; row++) {
        for (i = 0; i < 10; i++) {
            if (WORK->counters[row][i] >= 0) {
                func_0204f0d4(WORK->objects, WORK->counters[row][i]);
            }
            WORK->counters[row][i] = -1;
        }
    }
}
