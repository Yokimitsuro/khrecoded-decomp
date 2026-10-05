#include "nitro/types.h"

typedef struct FieldMenu {
    u8 pad_000[0x104];
    s32 mode;
    u8 pad_108[0x140 - 0x108];
    int hidden;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern void *GetSceneTagTracker(void);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);
extern void *FindLoadedElementById(void *tracker, int id);
extern void SetTagRecordArmed(void *tracker, void *entry, u32 flag);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);

void FieldMenu_SetHidden(int hidden)
{
    void *tracker = GetSceneTagTracker();
    FieldMenu *menu = data_ov001_020a04d0.menu;

    if (menu->hidden == hidden) {
        return;
    }
    menu->hidden = hidden;
    if (hidden != 0) {
        func_ov001_02075e10(menu, tracker, menu->mode);
        return;
    }
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 10), 0);
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 11), 0);
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 12), 0);
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 17), 0);
    SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 18), 0);
    func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x5d));
    func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x5b));
    func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x5c));
    func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x55));
}
