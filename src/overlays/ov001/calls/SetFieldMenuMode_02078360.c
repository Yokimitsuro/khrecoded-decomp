#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC4];
    s32 layout;
    s32 entryCount;
    s32 normalLayout;
    s32 normalCount;
    u8 pad_0D4[0x4];
    s32 commandCount;
    s32 commandEntry;
    u8 pad_0E0[0xC];
    s32 cursorIndex;
    u8 pad_0F0[0x4];
    s32 normalCursor;
    s32 commandCursor;
    u8 pad_0FC[0x8];
    s32 mode;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern u16 data_ov001_0209eea2[][4];
extern u16 data_ov001_0209ee8a[][4];

extern void *GetSceneTagTracker(void);
extern BOOL IsFieldFlag8Set(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, int mode);
extern void DrawMenuPanelPage(FieldMenu *menu);
extern void NNS_GfdRegisterNewVramTransferTask(int command, int offset, const void *src, int size);

void SetFieldMenuMode_02078360(int mode, BOOL refresh) {
    FieldMenu *menu = data_ov001_020a04d0.menu;
    void *tracker = GetSceneTagTracker();

    if (!IsFieldFlag8Set() && mode == 2) {
        return;
    }
    if (menu->mode == mode) {
        return;
    }
    switch (menu->mode) {
    case 0:
        menu->normalCursor = menu->cursorIndex;
        break;
    case 1:
        menu->commandCursor = menu->cursorIndex;
        break;
    case 2:
        break;
    }
    switch (mode) {
    case 0:
        menu->cursorIndex = menu->normalCursor;
        menu->layout = menu->normalLayout;
        menu->entryCount = menu->normalCount;
        break;
    case 1:
        if (menu->commandCount == 0) {
            return;
        }
        menu->cursorIndex = menu->commandCursor;
        menu->layout = 0xe;
        menu->entryCount = menu->commandCount;
        func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0x55));
        break;
    case 2:
        menu->cursorIndex = 0;
        menu->entryCount = menu->commandEntry;
        menu->layout = menu->entryCount;
        break;
    }
    menu->mode = mode;
    func_ov001_02075e10(menu, tracker, mode);
    if (refresh) {
        DrawMenuPanelPage(menu);
    }
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x30, data_ov001_0209eea2[mode], 8);
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x130, data_ov001_0209ee8a[mode], 8);
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x150, data_ov001_0209ee8a[mode], 8);
}
