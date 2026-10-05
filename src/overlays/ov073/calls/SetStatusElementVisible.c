#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern ResourceContainer *func_ov039_020bc1ec(void);
extern void *func_ov027_020b90c4(ResourceContainer *container, int id);
extern void func_ov027_020b95a0(ResourceContainer *container, void *element, BOOL visible);

void SetStatusElementVisible(int elementId, BOOL visible)
{
    ResourceContainer *container = func_ov039_020bc1ec();

    func_ov027_020b95a0(container, func_ov027_020b90c4(container, elementId), visible);
}
