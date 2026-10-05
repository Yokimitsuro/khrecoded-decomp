#include "nitro/types.h"

extern void *FindWidgetById(void *container, int elementId);
extern void func_ov027_020b95a0(void *container, void *element, BOOL visible);
extern void func_ov027_020b91e8(void *container, void *element, const s32 *position, int mode);

void PlaceElement42OrHide(void *container, const s32 *position)
{
    void *element = FindWidgetById(container, 0x2a);
    func_ov027_020b95a0(container, element, position != NULL);
    if (position != NULL) {
        func_ov027_020b91e8(container, element, position, 0);
    }
}
