#include "nitro/types.h"

typedef struct PanelSource {
    u8 pad_00[0xc];
    int resourceId;
} PanelSource;

typedef struct ResourcePanel {
    u8 pad_00[4];
    PanelSource *source;
    BOOL asyncLoad;
    u32 field;
} ResourcePanel;

typedef char *(*PathResolver)(int resourceId);

extern void *func_ov027_020ba134(char *path, int loadMode, void *callback, void *userData);
extern void func_ov025_020b6c2c(u32 owner, u32 entry);
extern void *func_0202c4a0(char *path, u32 heapId);
extern void func_ov025_020b6ad8(ResourcePanel *panel, void *data, u32 field);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadPanelResource(ResourcePanel *panel, PathResolver resolvePath)
{
    char *path = resolvePath(panel->source->resourceId);
    void *data;

    if (panel->asyncLoad) {
        func_ov027_020ba134(path, 1, func_ov025_020b6c2c, panel);
        return;
    }
    data = func_0202c4a0(path, 14);
    func_ov025_020b6ad8(panel, data, panel->field);
    NNSi_FndFreeFromDefaultHeap(data);
}
