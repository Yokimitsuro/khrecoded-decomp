#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0xcc];
    u8 saveData[0x3760];
} SaveSlot;

extern u8 *data_0205fe0c;
extern u32 func_ov039_020bc934(void);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void AcquireMapLayout(int reload, int keepExisting);
extern void RebuildRecordCounters(void);
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats(void *saveData, void *record, int rebuild, int flags);
extern void func_ov073_020c1ed4(void *saveData, void *options);
extern void func_02050a58(void);

void LoadSlotIntoGame(SaveSlot *slot)
{
    u8 *saveData;

    if (func_ov039_020bc934() == 3) {
        saveData = slot->saveData;
        if (slot->status < 2) {
            saveData = NULL;
        } else {
            func_01ff8ad8(saveData, data_0205fe0c, sizeof(slot->saveData));
        }
        AcquireMapLayout(1, 0);
        RebuildRecordCounters();
        ComputePlayerStats(data_0205fe0c, GetOverlaySelectionRecord(0), 1, 0);
        func_ov073_020c1ed4(saveData, NULL);
        func_02050a58();
    }
}
