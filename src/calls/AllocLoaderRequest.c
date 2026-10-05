#include "nitro/types.h"

typedef struct LoaderRequest {
    struct LoaderRequest *next;
} LoaderRequest;

typedef struct FileLoader {
    u8 pad_00[0x18];
    LoaderRequest *volatile freeList;
} FileLoader;

extern FileLoader gFileLoader;

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_0202c44c(void);

LoaderRequest *AllocLoaderRequest(void)
{
    int state = OS_DisableInterrupts();
    LoaderRequest *request;

    while (gFileLoader.freeList == NULL) {
        func_0202c44c();
    }
    request = gFileLoader.freeList;
    if (request != NULL) {
        gFileLoader.freeList = request->next;
        request->next = NULL;
    }
    OS_RestoreInterrupts(state);
    return request;
}
