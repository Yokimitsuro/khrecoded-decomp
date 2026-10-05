#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern int func_ov087_020c4778(void *scene, int headerMessageId, int footerMessageId);
extern void func_ov087_020c4c90(void *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void func_ov027_020b95a0(void *container, void *element, BOOL visible);

void OpenPromptMessage10(void *scene, int mode)
{
    void *container = func_ov039_020bc1dc();
    int frameId;
    void *frame;

    if (mode == 2) {
        frameId = func_ov087_020c4778(scene, 0x10, 0x17);
    } else {
        frameId = func_ov087_020c4778(scene, 0x10, 0x15);
    }
    func_ov087_020c4c90(scene);
    frame = FindWidgetById(container, frameId);
    func_ov027_020b95a0(container, frame, TRUE);
}


