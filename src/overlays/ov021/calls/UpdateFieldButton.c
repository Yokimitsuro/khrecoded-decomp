#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u16 entryValue;
    u8 pad_06[0xe];
    u8 entryIndex;
} FieldButton;

extern u8 data_ov021_020b5620;
extern void RefreshInputState(FieldButton *button);
extern BOOL func_ov001_02064490(void);
extern int func_ov001_02063a38(void);
extern BOOL HasFlagsAt0xe(FieldButton *button, u32 mask);
extern void func_ov021_020a6ff8(FieldButton *button);
extern void UpdateDirectionInput(FieldButton *button);
extern void func_ov021_020a70c8(FieldButton *button);
extern void func_ov021_020a7510(FieldButton *button);
extern void *GetBoundedEntryField(int index);
extern u16 func_ov058_020d5f24(void *entry, FieldButton *button);

void UpdateFieldButton(FieldButton *button)
{
    BOOL refresh;

    if (button->entryIndex == data_ov021_020b5620) {
        refresh = TRUE;
        RefreshInputState(button);
        if (func_ov001_02064490()) {
            refresh = FALSE;
        }
        if (func_ov001_02063a38() != 7 && HasFlagsAt0xe(button, 0x100) && HasFlagsAt0xe(button, 0x200)) {
            refresh = FALSE;
        }
        if (refresh) {
            func_ov021_020a6ff8(button);
            UpdateDirectionInput(button);
        }
        func_ov021_020a70c8(button);
        return;
    }
    func_ov021_020a7510(button);
    if (button->entryIndex != 0) {
        button->entryValue = func_ov058_020d5f24(GetBoundedEntryField(button->entryIndex), button);
        func_ov021_020a6ff8(button);
        UpdateDirectionInput(button);
    }
}
