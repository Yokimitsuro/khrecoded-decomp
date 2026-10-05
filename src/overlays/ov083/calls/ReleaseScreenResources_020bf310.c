#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct ScreenState {
    u8 pad_000[0xb8];
    TextLayer textLayers[2];
    u8 pad_120[0x150 - 0x120];
    StringTable strings;
    u8 pad_15c[0x168 - 0x15c];
    void *fileData;
} ScreenState;

typedef struct ResourceContainer ResourceContainer;

extern ResourceContainer *func_ov039_020bc1ec(void);
extern void *func_ov039_020bc1c4(void);
extern void FreePointerIfSet(void **ptr);
extern void func_ov027_020b833c(void *elements);
extern void DestroyAllContainerElements(ResourceContainer *container);
extern void ReleaseIfMarked(ResourceContainer *container);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseScreenResources_020bf310(ScreenState *screen) {
    ResourceContainer *container = func_ov039_020bc1ec();

    FreePointerIfSet(&screen->strings.buffer);
    func_ov027_020b833c(func_ov039_020bc1c4());
    DestroyAllContainerElements(container);
    ReleaseIfMarked(container);
    DestroyFndObjectList(&screen->textLayers[0]);
    DestroyFndObjectList(&screen->textLayers[1]);
    if (screen->fileData != NULL) {
        NNSi_FndFreeFromDefaultHeap(screen->fileData);
    }
}
