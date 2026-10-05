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
    int loadId;
    int loadMode;
    void *userData;
    FileLoadCallback callback;
    NNSFndLink link;
    u8 pad_20[0x4];
} FileLoadRequest;

extern NNSFndList *data_ov027_020ba3e4;
extern int data_0205fde4;
extern int data_0205fde0;

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern BOOL IsRecordIdFree(int id);
extern int func_0202c378(char *path, int mode);
extern int func_0202c38c(char *path, int mode);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);

void ProcessFileLoadQueue(void)
{
    NNSFndList *queue = data_ov027_020ba3e4;
    FileLoadRequest *request;

    if (data_0205fde4 != 0 || data_0205fde0 != 0) {
        return;
    }
    request = NNS_FndGetNextListObject(queue, NULL);
    if (request == NULL) {
        return;
    }
    switch (request->state) {
    case 0:
        if (IsRecordIdFree(0)) {
            if (request->loadMode != 0) {
                request->loadId = func_0202c38c(request->path, 14);
            } else {
                request->loadId = func_0202c378(request->path, 14);
            }
            request->state = 1;
        }
        break;
    case 1:
        if (IsRecordIdFree(request->loadId)) {
            request->state = 2;
            NNS_FndRemoveListObject(queue, request);
            NNS_FndAppendListObject(queue + 1, request);
            if (request->callback != NULL) {
                request->callback(request, request->userData);
            }
        }
        break;
    }
}
