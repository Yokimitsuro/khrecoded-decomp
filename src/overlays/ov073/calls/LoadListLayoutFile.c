#include "nitro/types.h"

typedef struct ListSource {
    u8 pad_00[0xc];
    int nameId;
} ListSource;

typedef struct ListLoader {
    u8 pad_00[4];
    ListSource *source;
    BOOL loadAsync;
    int layoutArg;
} ListLoader;

typedef char *(*PathResolver)(int nameId);

extern void *func_ov027_020ba134(char *path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void *func_0202c4a0(char *path, int heapTag);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov073_020c3550(ListLoader *loader, void *file, int layoutArg);
extern void OnListDataLoaded(void *request, void *userData);

void LoadListLayoutFile(ListLoader *loader, PathResolver resolvePath)
{
    char *path = resolvePath(loader->source->nameId);
    void *file;

    if (loader->loadAsync) {
        func_ov027_020ba134(path, 1, OnListDataLoaded, loader);
        return;
    }
    file = func_0202c4a0(path, 0xe);
    func_ov073_020c3550(loader, file, loader->layoutArg);
    NNSi_FndFreeFromDefaultHeap(file);
}
