#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    s32 state;
    u32 flags;
    u8 pad_08[0x10];
    TextLayer textLayer;
    u16 *text;
} PopupWindow;

extern u32 func_ov091_020c2798(PopupWindow *window, u32 mask);
extern void func_ov091_020c2784(PopupWindow *window, u32 mask);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int color);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void DestroyFndObjectList(TextLayer *layer);
extern void *G2S_GetBG2ScrPtr(void);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);

void ClosePopupText(PopupWindow *window)
{
    if (func_ov091_020c2798(window, 1)) {
        if (window->text != NULL) {
            NNSi_FndFreeFromDefaultHeap(window->text);
            window->text = NULL;
            CallVirtualHandlerSlot1(&window->textLayer, 0);
            FlushBufferAndRunCallback(&window->textLayer);
            DestroyFndObjectList(&window->textLayer);
        }
        func_ov091_020c2784(window, 1);
    }
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x800);
}
