#include "nitro/types.h"

typedef struct TextRect {
    int width;
    int height;
} TextRect;

typedef struct CardDate {
    u16 year : 7;
    u16 month : 4;
    u16 day : 5;
} CardDate;

typedef struct PlayerCard {
    u8 header[0x10];
    u16 name[0xb];
    u16 message[0x1b];
    CardDate date;
    u8 pad_5e[7];
    u8 titleId;
    u8 level;
    u8 rank;
    u8 avatarFrame;
    u8 pad_69[3];
    u8 capitalize;
    u8 pad_6d[3];
} PlayerCard;

typedef struct MenuState {
    u8 pad_00[0x9a];
    u8 phase9a : 2;
    u8 soundPlayed9a : 1;
    u8 highBits9a : 5;
    u8 pad_9b[0x2f0 - 0x9b];
    s8 progress;
    u8 pad_2f1[0x39c - 0x2f1];
    u8 objMain[0x100];
} MenuState;

extern MenuState *data_ov013_02074ce0;

extern void func_ov002_0206203c(int selector);
extern int DispatchContextCommand(int command, int value, int extra, void *buffer);
extern s32 func_ov013_02070cb4(void);
extern char *func_ov002_020621c4(int index, int extra);
extern void *OS_SNPrintf_0202e094(u16 *dst, unsigned int len, const char *fmt, ...);
extern u32 GetLanguageIndex(void);
extern u16 *CopyWideStringCapitalized(u16 *dst, const u16 *src, int size);
extern u16 *CopyWideStringWithNewline(u16 *dst, int size, const u16 *src, int breakIndex);
extern void DrawPanelSlotABText(int param1, int p2, int p3, int p4, int p5, int p6, int p7, u16 *text);
extern void func_ov002_02061dc8(int selectSecond, int arg2, int arg3, int arg4, int arg5, int arg6, char *text, int arg8);
extern void ActivatePanelSlotAB(int param1, int x, int y, int color, const void *value);
extern TextRect func_ov002_020627e8(int which, const void *text);
extern int CountFlaggedCategorySelections(void *selection);
extern int CountFilledCategorySelections(void *selection);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void StopSeqArcOrDefault(int seqArcNo, int index, int fadeFrames);
extern int *FindWidgetById(void *entries, int index);
extern void SetEntrySlotsVisible(void *entries, int *slot, BOOL visible);
extern void func_ov027_020b96c0(void *entries, int *slot, int frame);

void DrawPlayerCardDetails(void)
{
    u16 text[0x40] = {0};
    PlayerCard card;
    TextRect rect;
    CardDate date;
    int tens;
    int progress;
    void *container;

    func_ov002_0206203c(-1);
    progress = data_ov013_02074ce0->progress + 1;
    if (progress % 10 != 0) {
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1e00;
        DispatchContextCommand(0, func_ov013_02070cb4(), 0, &card);
        if (GetLanguageIndex() == 1) {
            if (card.capitalize) {
                ActivatePanelSlotAB(1, 0x1c, 0x20, 2, CopyWideStringCapitalized(text, card.name, 0x80));
            } else {
                ActivatePanelSlotAB(1, 0x1c, 0x20, 2, card.name);
            }
        } else {
            ActivatePanelSlotAB(1, 0x1c, 0x20, 2, card.name);
        }
        ActivatePanelSlotAB(1, 0x16, 0x51, 0xc, CopyWideStringWithNewline(text, 0x80, card.message, 0xd));
        rect = func_ov002_020627e8(1, func_ov002_020621c4(card.rank + 0x40, 0));
        ActivatePanelSlotAB(1, 0x52, 0x9c - rect.height / 2, 2, func_ov002_020621c4(card.rank + 0x40, 0));
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96c0(container, FindWidgetById(container, 10), card.avatarFrame);
        container = data_ov013_02074ce0->objMain;
        func_ov027_020b96c0(container, FindWidgetById(container, 0x14), (u16)(card.level % 10));
        tens = card.level / 10 % 10;
        if (tens != 0) {
            container = data_ov013_02074ce0->objMain;
            func_ov027_020b96c0(container, FindWidgetById(container, 0x15), (u16)tens);
            container = data_ov013_02074ce0->objMain;
            SetEntrySlotsVisible(container, FindWidgetById(container, 0x15), TRUE);
        } else {
            container = data_ov013_02074ce0->objMain;
            SetEntrySlotsVisible(container, FindWidgetById(container, 0x15), FALSE);
        }
        if (DispatchContextCommand(5, 0, 0, 0)) {
            container = data_ov013_02074ce0->objMain;
            SetEntrySlotsVisible(container, FindWidgetById(container, 8), TRUE);
            data_ov013_02074ce0->phase9a = 1;
            if (DispatchContextCommand(5, 0, 0, 0) && !data_ov013_02074ce0->soundPlayed9a) {
                PlaySoundEffect(2, 0xd);
                data_ov013_02074ce0->soundPlayed9a = 1;
            }
        }
        date = card.date;
        switch (GetLanguageIndex()) {
        case 0:
            OS_SNPrintf_0202e094(text, 0x40, func_ov002_020621c4(0x17, 0), date.year, date.month, date.day);
            break;
        case 1:
            OS_SNPrintf_0202e094(text, 0x40, func_ov002_020621c4(0x17, 0), date.month, date.day, date.year + 2000);
            break;
        default:
            OS_SNPrintf_0202e094(text, 0x40, func_ov002_020621c4(0x17, 0), date.day, date.month, date.year + 2000);
            break;
        }
        switch (GetLanguageIndex()) {
        case 3:
            DrawPanelSlotABText(1, 0, 0xb5, 0xfa, 0x10, 0xc, 0x800, text);
            break;
        default:
            DrawPanelSlotABText(1, 0, 0xb6, 0xfa, 0x10, 0xc, 0x800, text);
            break;
        }
        ActivatePanelSlotAB(1, 0x1c, 0x14, 10, func_ov002_020621c4(card.titleId, 0));
        OS_SNPrintf_0202e094(text, 0x40, func_ov002_020621c4(0x16, 0), CountFlaggedCategorySelections(&card),
                             CountFilledCategorySelections(&card));
        ActivatePanelSlotAB(0, 0xbe, 0x5c, 2, text);
    } else {
        func_ov002_02061dc8(1, 0x80, 0x4b, 2, 6, 10, func_ov002_020621c4(progress / 10 % 11 + 0x5f, 0), 0);
        *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
        container = data_ov013_02074ce0->objMain;
        SetEntrySlotsVisible(container, FindWidgetById(container, 8), FALSE);
        if (data_ov013_02074ce0->soundPlayed9a == 1) {
            StopSeqArcOrDefault(2, 0xd, 4);
            data_ov013_02074ce0->soundPlayed9a = 0;
        }
    }
}
