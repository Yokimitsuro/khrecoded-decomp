#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern int DrawPromptMessage(void *scene, int headerMessageId, int footerMessageId);
extern void ShowConfirmWindows(void *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void OpenPromptMessage11(void *scene, int mode)
{
    void *container = func_ov039_020bc1dc();
    int frameId;
    void *frame;

    if (mode == 2) {
        frameId = DrawPromptMessage(scene, 0x11, 0x17);
    } else {
        frameId = DrawPromptMessage(scene, 0x11, 0x15);
    }
    ShowConfirmWindows(scene);
    frame = FindWidgetById(container, frameId);
    SetEntrySlotsVisible(container, frame, TRUE);
}


