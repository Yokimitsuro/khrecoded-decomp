#include "nitro/types.h"

typedef struct TextRect {
    int width;
    int height;
} TextRect;

typedef struct Font {
    u8 data[0x5c];
} Font;

typedef struct OverlayWork {
    u8 pad_0000[0x644c];
    Font mainFont;
    u8 pad_64a8[0x689c - 0x64a8];
    s32 messageCount;
} OverlayWork;

typedef struct RecordEntry {
    u8 data[0x10];
} RecordEntry;

typedef struct TextCursor {
    u16 *text;
    int x;
    int y;
    BOOL continuous;
    int lineCount;
    int startX;
    int startY;
} TextCursor;

typedef struct TextWindow {
    int kind;
    int style;
    u8 pad_008[0x34];
    void *canvas;
    u8 pad_040[0x38];
    u16 widthTiles;
    u16 heightTiles;
    u8 pad_07c[0x8];
    u16 *lines[10];
    int lineIndex;
    int lineCount;
    RecordEntry bodyRecord;
    u8 pad_0c4[0x30];
    RecordEntry nameRecord;
    u8 pad_104[0x8];
    TextCursor *cursor;
} TextWindow;

extern u16 data_02060500;
extern OverlayWork *gTextWindowResourceTable;
extern TextRect NNSi_G2dFontGetTextRect(const Font *font, int hSpace, int vSpace, const void *text);
extern void SetTimerDuration(TextWindow *window, int duration);
extern void SetRecordEntryEnabled(RecordEntry *entry, int enabled);
extern void CallVirtualHandlerSlot1(void **context, int arg);
extern void FlushBufferAndRunCallback(void **context);
extern void func_ov036_020c2814(void);

static inline TextRect MeasureLine(const u16 *text)
{
    return NNSi_G2dFontGetTextRect(&gTextWindowResourceTable->mainFont, 0, 2, text);
}

void AdvanceTextWindowPage(TextWindow *window)
{
    if (!(data_02060500 & 1) && !(data_02060500 & 0x200) && !(data_02060500 & 0x100) && !(data_02060500 & 0x80)) {
        return;
    }
    if (window->kind != 1 && ++window->lineIndex < window->lineCount) {
        switch (window->kind) {
        case 4: {
            TextCursor *cursor = window->cursor;
            TextRect size = MeasureLine(window->lines[window->lineIndex]);

            cursor->startX = (window->widthTiles * 8) / 2 - size.width / 2;
            cursor->startY = (window->heightTiles * 8) / 2 - size.height / 2 - 1;
            cursor->x = cursor->startX;
            cursor->y = cursor->startY;
            cursor->continuous = FALSE;
            cursor->lineCount = 0;
            cursor->text = window->lines[window->lineIndex];
            SetTimerDuration(window, 6);
            SetRecordEntryEnabled(&window->bodyRecord, 0);
            switch (window->style) {
            case 3:
            case 4:
            case 5:
            case 6:
            case 15:
                CallVirtualHandlerSlot1(&window->canvas, 12);
                break;
            case 14:
                CallVirtualHandlerSlot1(&window->canvas, 0);
                break;
            default:
                CallVirtualHandlerSlot1(&window->canvas, 1);
                break;
            }
            FlushBufferAndRunCallback(&window->canvas);
            func_ov036_020c2814();
            return;
        }
        case 0: {
            TextCursor *cursor = window->cursor;
            TextRect size = MeasureLine(window->lines[window->lineIndex]);

            cursor->startX = (window->widthTiles * 8) / 2 - size.width / 2;
            cursor->startY = (window->heightTiles * 8) / 2 - size.height / 2 - 1;
            cursor->x = cursor->startX;
            cursor->y = cursor->startY;
            cursor->continuous = FALSE;
            cursor->lineCount = 0;
            cursor->text = window->lines[window->lineIndex];
            SetTimerDuration(window, 6);
            SetRecordEntryEnabled(&window->bodyRecord, 0);
            switch (window->style) {
            case 3:
            case 4:
            case 5:
            case 6:
                CallVirtualHandlerSlot1(&window->canvas, 12);
                break;
            case 14:
                CallVirtualHandlerSlot1(&window->canvas, 0);
                break;
            default:
                CallVirtualHandlerSlot1(&window->canvas, 1);
                break;
            }
            FlushBufferAndRunCallback(&window->canvas);
            func_ov036_020c2814();
            return;
        }
        }
    }
    func_ov036_020c2814();
    if (gTextWindowResourceTable->messageCount > 0) {
        SetTimerDuration(window, 13);
        return;
    }
    SetRecordEntryEnabled(&window->bodyRecord, 0);
    SetRecordEntryEnabled(&window->nameRecord, 0);
    SetTimerDuration(window, 9);
}
