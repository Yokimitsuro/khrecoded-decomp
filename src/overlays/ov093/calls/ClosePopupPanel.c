#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int slotIndex;
} PopupManager;

extern PopupManager *data_ov093_020c5104;
extern void SetBgSubLayerVisible(void *machine, BOOL visible);
extern void func_ov093_020c319c(int slotIndex, BOOL visible);
extern void func_ov093_020c2f3c(void *work);
extern void StateMachine_SetState(void *machine, int state);

void ClosePopupPanel(void *machine)
{
    SetBgSubLayerVisible(machine, FALSE);
    func_ov093_020c319c(data_ov093_020c5104->slotIndex, FALSE);
    func_ov093_020c2f3c(machine);
    StateMachine_SetState(machine, 0);
}
