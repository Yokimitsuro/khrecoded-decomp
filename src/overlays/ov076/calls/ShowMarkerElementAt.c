#include "nitro/types.h"

extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void func_ov027_020b91e8(void *container, void *element, const s32 *position, int mode);

void ShowMarkerElementAt(void *container, const s32 *position)
{
    void *marker = FindWidgetById(container, 0x2a);

    SetEntrySlotsVisible(container, marker, position != NULL);
    if (position != NULL) {
        func_ov027_020b91e8(container, marker, position, 0);
    }
}
