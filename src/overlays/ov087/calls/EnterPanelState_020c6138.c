#include "nitro/types.h"

typedef void (*StateEnterFunc)(void *scene, int previousState);

typedef struct {
    StateEnterFunc handlers[18];
} StateHandlerTable;

extern const StateHandlerTable gSelectionPanelStateHandlers;
extern void *func_ov039_020bc1dc(void);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void InvokeSlotHandlers(void *scene);
extern void func_ov087_020c4a68(void *scene);

void EnterPanelState_020c6138(void *scene, int stateId, int previousState)
{
    void *container = func_ov039_020bc1dc();
    StateHandlerTable table = gSelectionPanelStateHandlers;
    StateEnterFunc handler;

    SetEntrySlotsVisible(container, FindWidgetById(container, 0xc), FALSE);
    handler = table.handlers[stateId];
    if (handler == NULL) {
        return;
    }
    InvokeSlotHandlers(scene);
    func_ov087_020c4a68(scene);
    handler(scene, previousState);
}
