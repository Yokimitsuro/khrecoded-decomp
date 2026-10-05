#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 data[0xc];
} PackedFileView;

typedef struct {
    u8 pad_0000[0x18];
    u8 font[0xC];
    TextLayer layers[4];
    u8 pad_00F4[0xCB64 - 0xF4];
    PackedFileView views[3];
} Ov103State;

extern void CallVirtualHandlerSlot1(TextLayer *layer, int arg);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern void FreePointerIfSet(PackedFileView *view);
extern BOOL FreeResourceBufferAndProbeHeap(void *resource);

void FreeTextLayers(Ov103State *state)
{
    int i;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1(&state->layers[i], 0);
        FlushBufferAndRunCallback(&state->layers[i]);
        DestroyFndObjectList(&state->layers[i]);
    }
    for (i = 0; i < 3; i++) {
        FreePointerIfSet(&state->views[i]);
    }
    FreeResourceBufferAndProbeHeap(state->font);
}
