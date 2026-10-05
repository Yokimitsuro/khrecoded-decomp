#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern int func_ov087_020c4778(void *scene, int headerMessageId, int footerMessageId);
extern void func_ov087_020c4c90(void *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void func_ov027_020b95a0(void *container, void *element, BOOL visible);

void OpenPromptMessage12(void *scene)
{
    void *container = func_ov039_020bc1dc();
    int frameId = func_ov087_020c4778(scene, 0x12, 0x17);
    void *frame;

    func_ov087_020c4c90(scene);
    frame = FindWidgetById(container, frameId);
    func_ov027_020b95a0(container, frame, TRUE);
}
