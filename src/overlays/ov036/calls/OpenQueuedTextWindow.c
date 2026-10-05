#include "nitro/types.h"

typedef struct TextWindowRequest {
    s32 type;
    s32 style;
    s32 speaker;
    s32 x;
    s32 y;
    s32 fadeFrames;
    u16 *text;
    s32 optionA;
    s32 optionB;
    s32 screen;
} TextWindowRequest;

typedef struct OverlayWork {
    u8 pad_0000[0x682c];
    s32 openCount;
    u8 pad_6830[0x684c - 0x6830];
    TextWindowRequest request;
    TextWindowRequest nextRequest;
    s32 messageCount;
    s32 choiceResult;
} OverlayWork;

typedef struct DialogCursor {
    u16 *text;
    u8 pad_04[0x1c];
    s32 portraitId;
    s32 speaker;
    s32 fadeOut;
    s32 fadeIn;
    s32 delay;
    s32 tileWidth;
    s32 tileHeight;
    s32 blendStart;
    s32 fadeFrames;
    s32 color;
} DialogCursor;

typedef struct BannerCursor {
    u16 *text;
    u8 pad_04[0x18];
    s32 speaker;
    s32 fadeOut;
    s32 fadeIn;
    s32 delay;
    s32 tileWidth;
    s32 tileHeight;
    s32 blendStart;
    s32 fadeFrames;
    s32 color;
} BannerCursor;

typedef struct ChoiceCursor {
    u8 pad_00[0xc];
    s32 optionA;
    u8 pad_10[0x4];
    s32 optionB;
} ChoiceCursor;

typedef struct TextWindow {
    s32 type;
    s32 style;
    s32 duration;
    s32 unk_0c;
    s32 elapsed;
    s32 x;
    s32 y;
    s32 screen;
    s32 tileBase;
    s32 tileLimit;
    s32 paletteBase;
    s32 mapBase;
    u8 pad_30[0x4];
    s32 unk_34;
    u8 pad_38[0x38];
    u16 *text;
    u8 pad_74[0x10];
    u16 *lines[10];
    s32 lineIndex;
    s32 lineCount;
    u8 pad_b4[0x58];
    void *cursor;
} TextWindow;

#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)

extern OverlayWork *gTextWindowResourceTable;
extern const s32 data_ov036_020c33c8[];
extern const s32 data_ov036_020c33c0[];
extern const s32 data_ov036_020c33b0[];
extern const s32 data_ov036_020c33b8[];
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void SetTimerDuration(TextWindow *window, int duration);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

#define DIALOG ((DialogCursor *)window->cursor)
#define BANNER ((BannerCursor *)window->cursor)
#define ROUND_FX(v) ((v) > 0 ? (int)(0.5f + (float)((v) << 12)) : (int)((float)((v) << 12) - 0.5f))

static inline void SetBG2Priority(int priority)
{
    REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | priority);
}

static inline void SetBG3Priority(int priority)
{
    REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | priority);
}

void OpenQueuedTextWindow(TextWindow *window)
{
    OverlayWork *work = gTextWindowResourceTable;
    TextWindowRequest *request;
    u16 *cursor;
    s32 screen;

    window->type = work->request.type;
    request = &work->request;
    window->style = request->style;
    screen = request->screen;
    window->screen = screen;
    window->tileBase = data_ov036_020c33c8[screen];
    window->tileLimit = data_ov036_020c33c0[screen];
    window->paletteBase = data_ov036_020c33b0[screen];
    window->text = NULL;
    window->mapBase = data_ov036_020c33b8[screen];
    window->unk_0c = 0;
    window->unk_34 = 0;
    window->x = request->x - 0x80;
    window->y = request->y - 0x60;
    window->text = request->text;
    gTextWindowResourceTable->openCount++;
    cursor = window->text;
    window->lineIndex = 0;
    window->lineCount = 0;
    if (cursor != NULL) {
        window->lines[window->lineCount] = cursor;
        window->lineCount++;
        for (; *cursor != 0; cursor++) {
            if (*cursor == 3) {
                *cursor++ = 0;
                window->lines[window->lineCount] = cursor;
                window->lineCount++;
            }
        }
    }
    switch (window->type) {
    case 1:
        window->cursor = NNS_FndAllocFromDefaultExpHeapEx(sizeof(ChoiceCursor), -4);
        ((ChoiceCursor *)window->cursor)->optionA = request->optionA;
        ((ChoiceCursor *)window->cursor)->optionB = request->optionB;
        gTextWindowResourceTable->choiceResult = -1;
        break;
    case 2:
    case 3:
        break;
    case 0:
        window->cursor = NNS_FndAllocFromDefaultExpHeapEx(sizeof(DialogCursor), -4);
        DIALOG->speaker = request->speaker;
        DIALOG->portraitId = -1;
        DIALOG->text = window->lines[window->lineIndex];
        DIALOG->delay = 0;
        DIALOG->blendStart = 8;
        DIALOG->fadeFrames = ROUND_FX(request->fadeFrames);
        DIALOG->fadeIn = DIALOG->fadeFrames;
        DIALOG->fadeOut = DIALOG->fadeIn;
        DIALOG->tileHeight = 0;
        DIALOG->tileWidth = DIALOG->tileHeight;
        switch (window->style) {
        case 3:
        case 4:
        case 5:
        case 6:
            DIALOG->color = 13;
            break;
        case 14:
            DIALOG->color = 9;
            break;
        default:
            DIALOG->color = 3;
            break;
        }
        break;
    case 4:
        window->cursor = NNS_FndAllocFromDefaultExpHeapEx(sizeof(BannerCursor), -4);
        BANNER->speaker = request->speaker;
        BANNER->text = window->lines[window->lineIndex];
        BANNER->delay = 0;
        BANNER->blendStart = 8;
        BANNER->fadeFrames = ROUND_FX(request->fadeFrames);
        BANNER->fadeIn = BANNER->fadeFrames;
        BANNER->fadeOut = BANNER->fadeIn;
        BANNER->tileHeight = 0;
        BANNER->tileWidth = BANNER->tileHeight;
        switch (window->style) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 15:
            BANNER->color = 13;
            break;
        case 14:
            BANNER->color = 9;
            break;
        default:
            BANNER->color = 3;
            break;
        }
        break;
    }
    if (window->screen == 0) {
        SetBG2Priority(3);
    } else {
        SetBG3Priority(3);
    }
    SetTimerDuration(window, 2);
    MIi_CpuCopyFast(&gTextWindowResourceTable->nextRequest, &gTextWindowResourceTable->request, sizeof(TextWindowRequest));
    gTextWindowResourceTable->messageCount--;
}
