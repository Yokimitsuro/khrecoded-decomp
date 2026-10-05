#include "nitro/types.h"

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef void (*FileLoadCallback)(void *request, void *userData);

typedef struct FileLoadRequest {
    int state;
    char *path;
    void *buffer;
    int loadMode;
    void *userData;
    FileLoadCallback callback;
    NNSFndLink link;
    u8 pad_20[0x4];
} FileLoadRequest;

extern NNSFndList *data_ov027_020ba3e4;

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuFill8(void *dest, int value, u32 size);
extern int STD_GetStringLength(const char *str);
extern char *STD_CopyString(char *destp, const char *srcp);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);

FileLoadRequest *QueueFileLoadRequest(char *path, int loadMode, FileLoadCallback callback, void *userData) {
    FileLoadRequest *request;
    char *pathCopy;

    request = NNS_FndAllocFromDefaultExpHeapEx(sizeof(FileLoadRequest), -4);
    MI_CpuFill8(request, 0, sizeof(FileLoadRequest));
    if ((u32)path & 0x80000000) {
        request->path = path;
    } else {
        pathCopy = NNS_FndAllocFromDefaultExpHeapEx(STD_GetStringLength(path) + 1, -4);
        request->path = pathCopy;
        STD_CopyString(pathCopy, path);
    }
    request->callback = callback;
    request->userData = userData;
    request->loadMode = loadMode;
    NNS_FndAppendListObject(data_ov027_020ba3e4, request);
    return request;
}
