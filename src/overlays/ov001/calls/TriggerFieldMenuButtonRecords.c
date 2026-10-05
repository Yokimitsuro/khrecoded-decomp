#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 entryCount;
    u8 pad_0CC[0x6C];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00 : 9;
    u32 altControls : 1;
    u32 unk_10 : 6;
    u32 swapActions : 1;
} ControlConfig;

typedef struct {
    u8 pad_0000[0x2878];
    ControlConfig controls;
} SaveData;

typedef struct {
    u32 recordIds[2][2][3];
} ButtonRecordTable;

extern const ButtonRecordTable data_ov001_0209df0c;
extern SaveData *data_0205fe0c;

extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);

void TriggerFieldMenuButtonRecords(FieldMenu *menu)
{
    ButtonRecordTable table = data_ov001_0209df0c;
    void *pool = GetSceneTagTracker();
    u32 *recordIds;

    if (menu->unk_138 == 0) {
        return;
    }
    recordIds = table.recordIds[data_0205fe0c->controls.altControls][data_0205fe0c->controls.swapActions];
    func_ov027_020b8230(pool, FindActiveRecordById(pool, recordIds[2]));
    if (menu->entryCount < 2) {
        return;
    }
    func_ov027_020b8230(pool, FindActiveRecordById(pool, recordIds[0]));
    func_ov027_020b8230(pool, FindActiveRecordById(pool, recordIds[1]));
}
