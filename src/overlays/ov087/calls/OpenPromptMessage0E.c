#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern int DrawPromptMessage(void *scene, int headerMessageId, int footerMessageId);
extern void ShowConfirmWindows(void *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void OpenPromptMessage0E(void *scene)
{
    void *container = func_ov039_020bc1dc();
    int frameId = DrawPromptMessage(scene, 0x0e, 0x15);
    void *frame;

    ShowConfirmWindows(scene);
    frame = FindWidgetById(container, frameId);
    SetEntrySlotsVisible(container, frame, TRUE);
}
