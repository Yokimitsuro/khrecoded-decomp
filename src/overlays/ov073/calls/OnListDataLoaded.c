#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0xc];
    void *workBuffer;
} ListView;

extern void *func_ov027_020ba1f8(void *request);
extern void LoadListViewGraphics(ListView *list, void *data, void *workBuffer);
extern void func_ov027_020ba200(void *request, BOOL freeData);

void OnListDataLoaded(void *request, ListView *list)
{
    LoadListViewGraphics(list, func_ov027_020ba1f8(request), list->workBuffer);
    func_ov027_020ba200(request, TRUE);
}
