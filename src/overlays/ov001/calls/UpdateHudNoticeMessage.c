#include "nitro/types.h"

#define NOTICE_DISPLAY_TICKS 0xffb10

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x84 - 0x1c];
    u8 font[0x484 - 0x84];
    s32 pendingNoticeKind;
    u16 *pendingText;
    u16 *queuedText;
    u16 customText[0x20];
    u64 noticeTick;
    u8 textWindow[0x50c - 0x4d8];
    u8 messageTable[0x133c - 0x50c];
    s32 bannerCounter;
} HudContext;

extern u64 OS_GetTick(void);
extern u16 *func_ov027_020b9e10(HudContext *hud, int layer);
extern int func_02029f5c(void);
extern BOOL IsHudFlag9Set(void);
extern BOOL func_ov001_02064490(void);
extern BOOL func_ov001_02072040(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b8288(void *pool, void *record);
extern void func_ov027_020b824c(void *pool, void *record, s16 offset, s16 duration);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void CallVirtualHandlerSlot1(void *window, int arg);
extern void func_02001620(void *window, u32 x, u32 y, u32 color, u32 flags, u16 *text,
                          void *font, int maxWidth);
extern void PlaySoundChecked(int channel, int soundId);
extern void Text_UploadTileBuffer(void *window);
extern void FillBackgroundLayerRect(void *window, u16 *dst, int x, int y, u8 palette);

void UpdateHudNoticeMessage(HudContext *hud)
{
    u64 now;
    u16 *layer;
    int blocked;
    BOOL redraw;
    int messageIndex;
    s32 counter;

    now = OS_GetTick();
    layer = func_ov027_020b9e10(hud, 0xb);
    blocked = func_02029f5c();

    if (hud->noticeTick != 0 && now >= hud->noticeTick + NOTICE_DISPLAY_TICKS) {
        func_ov027_020b8288(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x38));
        hud->noticeTick = 0;
    }

    if (!IsHudFlag9Set() && !func_ov001_02064490() && blocked == 0 && hud->noticeTick == 0) {
        redraw = TRUE;
        CallVirtualHandlerSlot1(hud->textWindow, 1);
        if (hud->pendingNoticeKind > 0 && hud->queuedText == NULL) {
            func_ov027_020b8230(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x33));
            messageIndex = 0;
            PlaySoundChecked(0, 0x13);
            if (hud->pendingNoticeKind != 1) {
                messageIndex = 1;
            }
            func_02001620(hud->textWindow, 0x4e, 0, 2, 0x821, func_ov027_020ba2c8(hud->messageTable, messageIndex),
                          hud->font, 0x4e);
            hud->noticeTick = now;
            hud->pendingNoticeKind = 0;
        } else if (hud->pendingText != NULL) {
            func_ov027_020b8230(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x38));
            func_02001620(hud->textWindow, 0x4e, 0, 2, 0x821, hud->pendingText, hud->font, 0x4e);
            hud->noticeTick = now;
            hud->pendingText = NULL;
            hud->queuedText = func_ov027_020ba2c8(hud->messageTable, 3);
        } else if (hud->queuedText != NULL) {
            func_ov027_020b8230(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x38));
            func_02001620(hud->textWindow, 0x4e, 0, 2, 0x821, hud->queuedText, hud->font, 0x4e);
            hud->noticeTick = now;
            hud->queuedText = NULL;
        } else if (hud->customText[0] != 0) {
            func_ov027_020b8230(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x37));
            PlaySoundChecked(0, 0x13);
            func_02001620(hud->textWindow, 0x4e, 0, 2, 0x821, hud->customText, hud->font, 0x4e);
            hud->noticeTick = now;
            hud->customText[0] = 0;
        } else {
            redraw = FALSE;
        }
        if (redraw) {
            Text_UploadTileBuffer(hud->textWindow);
            FillBackgroundLayerRect(hud->textWindow, layer, 0x16, 7, 0xf);
        }
    }

    if (hud->bannerCounter > 0) {
        counter = hud->bannerCounter + 1;
        hud->bannerCounter = counter;
        if (counter <= 8) {
            func_ov027_020b824c(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x39),
                                counter - 8, 10);
        } else if (counter > 0x44) {
            if (!func_ov001_02072040()) {
                func_ov027_020b8288(hud->recordPool, FindActiveRecordById(hud->recordPool, 0x39));
            }
            hud->bannerCounter = 0;
        }
    }
}
