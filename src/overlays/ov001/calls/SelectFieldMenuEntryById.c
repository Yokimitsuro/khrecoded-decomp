#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xEC];
    s32 cursorIndex;
    u8 pad_0F0[0x48];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsLeadEntryFlag80Set(void);
extern void *FindFieldMenuEntryById(FieldMenu *menu, int listKind, int entryId, s32 *outIndex);
extern void func_ov001_020769f4(FieldMenu *menu);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SelectFieldMenuEntryById(int entryId)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;

    if (menu->unk_138 == 0) {
        return;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return;
    }
    if (IsLeadEntryFlag80Set()) {
        return;
    }
    FindFieldMenuEntryById(menu, 0, entryId, &menu->cursorIndex);
    func_ov001_020769f4(menu);
    PlaySoundEffect(0, 0);
}
