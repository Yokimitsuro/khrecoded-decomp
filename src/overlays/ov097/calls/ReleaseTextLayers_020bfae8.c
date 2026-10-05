#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    void *buffer;
    u8 pad_04[8];
} GlyphBuffer;

typedef struct {
    u8 pad_0000[0x24];
    u8 resource[0xc];
    TextLayer layers[4];
    u8 pad_0100[0xcde4 - 0x100];
    GlyphBuffer glyphBuffers[3];
} MenuScene;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern BOOL DestroyFndObjectList(void *container);
extern void FreePointerIfSet(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap(void *resource);

void ReleaseTextLayers_020bfae8(MenuScene *scene)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1(&scene->layers[i], 0);
        FlushBufferAndRunCallback(&scene->layers[i]);
        DestroyFndObjectList(&scene->layers[i]);
    }
    for (j = 0; j < 3; j++) {
        FreePointerIfSet(&scene->glyphBuffers[j]);
    }
    FreeResourceBufferAndProbeHeap(scene->resource);
}
