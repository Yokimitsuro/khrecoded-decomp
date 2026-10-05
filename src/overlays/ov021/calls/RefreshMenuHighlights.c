#include "nitro/types.h"

typedef struct {
    s32 id;
    s32 category;
} MenuMember;

typedef struct {
    MenuMember **members;
    s32 count;
    MenuMember *pad_08;
    void *current;
    u32 pad_10;
    s32 player;
} MemberList;

typedef struct PlayerEntry PlayerEntry;
struct PlayerEntry {
    u8 pad_00[0x1dc];
    s32 mode;
    u8 pad_1e0[0x4c];
    s32 (*getMode)(PlayerEntry *entry);
};

extern PlayerEntry *GetBoundedEntryField(int player);
extern int func_ov001_0206dc38(void);
extern BOOL func_ov001_020645c8(u32 flag);
extern int func_ov001_02064784(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_0206e224(void);
extern void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted);

void RefreshMenuHighlights(MemberList *list)
{
    BOOL enabled = TRUE;
    BOOL specialEnabled = TRUE;
    int i;
    PlayerEntry *entry;
    s32 mode;
    int count;

    if (list->player != 0) {
        return;
    }
    entry = GetBoundedEntryField(list->player);
    if (func_ov001_0206dc38() <= 1) {
        if (func_ov001_020645c8(0x3520)) {
            enabled = FALSE;
        } else {
            switch (func_ov001_02064784()) {
            case 2:
                if (func_ov001_020645c8(0x3718)) {
                    enabled = FALSE;
                    specialEnabled = FALSE;
                }
                break;
            case 7:
                if (func_ov001_020645c8(0x370c)) {
                    enabled = FALSE;
                    specialEnabled = FALSE;
                }
                if (func_ov001_020645c8(0x370d)) {
                    enabled = FALSE;
                    specialEnabled = FALSE;
                }
                break;
            }
        }
    }
    if (entry->getMode != NULL) {
        mode = entry->getMode(entry);
    } else {
        mode = entry->mode;
    }
    if (mode == 2 || mode == 4 || mode == 8) {
        enabled = FALSE;
        specialEnabled = FALSE;
    }
    count = list->count;
    if (list->current != NULL) {
        count--;
    }
    for (i = 0; i < count; i++) {
        MenuMember *member = list->members[i];
        if (member != NULL && func_ov001_02063a38() != 6) {
            if (member->category != 1) {
                SetMenuEntryHighlight(0, i, enabled);
            } else {
                BOOL highlight = specialEnabled;
                switch (member->id) {
                case 0xb9:
                case 0xba:
                    if (!func_ov001_0206e224()) {
                        highlight = FALSE;
                    }
                    if (entry->getMode != NULL) {
                        mode = entry->getMode(entry);
                    } else {
                        mode = entry->mode;
                    }
                    if (mode == 10) {
                        highlight = FALSE;
                    }
                    break;
                }
                SetMenuEntryHighlight(0, i, highlight);
            }
        }
    }
}
