#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[0x10];
    u8 font[0xc];
    TextLayer textLayers[2];
    u8 pad_84[0xc9e8 - 0x84];
    void *unk_C9E8;
} MenuScene;

extern void CallVirtualHandlerSlot1(TextLayer *layer, int color);
extern void FlushBufferAndRunCallback(TextLayer *layer);
extern void DestroyFndObjectList(TextLayer *layer);
extern void FreePointerIfSet(void **pointer);
extern void FreeResourceBufferAndProbeHeap(void *font);

void ReleaseTextLayers(MenuScene *scene)
{
    int i;

    for (i = 0; i < 2; i++) {
        CallVirtualHandlerSlot1(&scene->textLayers[i], 0);
        FlushBufferAndRunCallback(&scene->textLayers[i]);
        DestroyFndObjectList(&scene->textLayers[i]);
    }
    FreePointerIfSet(&scene->unk_C9E8);
    FreeResourceBufferAndProbeHeap(scene->font);
}
