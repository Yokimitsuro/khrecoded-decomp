#include "nitro/types.h"

typedef struct {
    u8 flagIndex;
    u8 messageId;
    s8 messageArg;
    s8 hasPopup;
    s16 popupId;
    u8 pad_06[6];
} UnlockEntry;

typedef struct {
    u8 pad_00[2];
    u8 type;
} EventInfo;

typedef struct ResourceContainer ResourceContainer;

typedef struct {
    s32 bonusPending;
    s32 active;
    const UnlockEntry *entry;
} UnlockPopup;

typedef struct {
    u8 pad_00000[7];
    u8 needsRedraw;
    u8 pad_00008[0x80 - 0x8];
    s32 closeRequested;
    u8 pad_00084[0x4ee0 - 0x84];
    int messageBank[0x4];
    u8 pad_04ef0[0x11fac - 0x4ef0];
    void *currentMessage;
    u8 pad_11fb0[0x12dd4 - 0x11fb0];
    EventInfo *eventInfo;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    ResourceContainer *layout;
    u8 pad_131a8[0x13e66 - 0x131a8];
    s16 bonusKind;
    u8 pad_13e68[0x13e70 - 0x13e68];
    s32 unk_13e70;
    u8 pad_13e74[0x1751c - 0x13e74];
    UnlockPopup popup;
} MatrixMenu;

typedef struct {
    u8 pad_0000[0x2c58];
    s32 unk_2c58;
    u8 pad_2c5c[0x2c67 - 0x2c5c];
    u8 unlockCount;
    u8 unk_2c68;
    u8 pad_2c69;
    u8 unk_2c6a;
} SaveBlock;

extern SaveBlock *data_0205fe0c;
extern const UnlockEntry data_ov075_020d1580[];
extern BOOL func_ov075_020c42f4(int unlockId, BOOL queryOnly);
extern void ShowDialogMessageAt(MatrixMenu *menu, int messageId, int unused, int messageArg, int flags);
extern u16 GetByteCounterOrDefault(int index);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern void *func_ov027_020ba2c8(int *bank, int index);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void SetUnlockableElementsVisible(ResourceContainer *layout, BOOL visible);

BOOL ShowNextUnlockNotice(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly)
{
    s32 unlockCount = data_0205fe0c->unlockCount;
    s32 noticeIndex = -1;
    s32 unlockId;
    EventInfo *event;
    const UnlockEntry *entry;

    if (!eventMode) {
        if (!func_ov075_020c42f4(0, queryOnly)) {
            noticeIndex = 0;
            goto done;
        }
        if (!func_ov075_020c42f4(1, queryOnly)) {
            noticeIndex = 1;
            goto done;
        }
        if (!func_ov075_020c42f4(2, queryOnly)) {
            noticeIndex = 2;
            goto done;
        }
        if (unlockCount != 0 && !func_ov075_020c42f4(3, queryOnly)) {
            noticeIndex = 3;
            goto done;
        }
        if (unlockCount != 0 && !func_ov075_020c42f4(4, queryOnly)) {
            noticeIndex = 4;
            goto done;
        }
        if (unlockCount != 0 && !func_ov075_020c42f4(5, queryOnly)) {
            noticeIndex = 5;
            goto done;
        }
        if (unlockCount > 1 && !func_ov075_020c42f4(6, queryOnly)) {
            noticeIndex = 6;
            goto done;
        }
        if (unlockCount > 2) {
            unlockId = 7;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (GetByteCounterOrDefault(0x160) != 0 || GetByteCounterOrDefault(0x161) != 0) {
            unlockId = 13;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (data_0205fe0c->unk_2c58 != 0) {
            unlockId = 10;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (data_0205fe0c->unk_2c6a != 0) {
            unlockId = 12;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (data_0205fe0c->unk_2c68 != 0) {
            unlockId = 11;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (menu->popup.bonusPending != 0 && menu->bonusKind == 2) {
            unlockId = 14;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (menu->popup.bonusPending != 0 && menu->bonusKind == 1) {
            unlockId = 15;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (menu->popup.bonusPending != 0 && menu->bonusKind == 3) {
            unlockId = 16;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (menu->popup.bonusPending != 0 && menu->bonusKind == 4) {
            unlockId = 17;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (ReadGlobalPackedBits(0x1a0f, 3) >= 2) {
            unlockId = 18;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto done;
            }
        }
        if (!queryOnly) {
            menu->popup.bonusPending = 0;
            menu->popup.active = 0;
            menu->currentMessage = func_ov027_020ba2c8(menu->messageBank, 0x58);
            menu->needsRedraw = 1;
            return FALSE;
        }
    } else {
        event = menu->eventInfo;
        if (event->type == 9 && !func_ov075_020c42f4(8, queryOnly)) {
            noticeIndex = 8;
        close:
            menu->closeRequested = 1;
            menu->unk_13e70 = 0;
            SetUnlockableElementsVisible(menu->layout, FALSE);
            goto done;
        }
        if (event->type == 4 || event->type == 5) {
            unlockId = 9;
            if (!func_ov075_020c42f4(unlockId, queryOnly)) {
                noticeIndex = unlockId;
                goto close;
            }
        }
        if (!queryOnly) {
            return FALSE;
        }
    }
done:
    if (queryOnly) {
        if (noticeIndex < 0) {
            return FALSE;
        }
        return TRUE;
    }
    menu->popup.bonusPending = 0;
    entry = &data_ov075_020d1580[noticeIndex];
    if (entry->popupId < 0) {
        if (entry->hasPopup == 0) {
            menu->popup.entry = NULL;
            ShowDialogMessageAt(menu, entry->messageId, 0, entry->messageArg, 1);
        } else {
            menu->popup.entry = entry;
            menu->popup.active = 1;
        }
    } else {
        menu->popup.entry = entry;
        menu->popup.active = 1;
    }
    menu->currentMessage = NULL;
    menu->needsRedraw = 1;
    SetSecondaryElementEnabled(FALSE);
    return TRUE;
}
