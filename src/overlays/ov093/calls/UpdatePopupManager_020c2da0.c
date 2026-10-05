#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

typedef struct {
    u8 pad_000[0x2c];
    StateMachine machine;
    u8 pad_038[0x26c - 0x38];
    int pendingCount;
} PopupManager;

typedef void (*PopupStateHandler)(StateMachine *machine);

extern PopupManager *data_ov093_020c5104;
extern const PopupStateHandler data_ov093_020c3e74[];
extern int func_ov093_020c3bf4(StateMachine *machine);
extern void MIi_CpuClearFast(int value, void *dest, int size);
extern void StateMachine_SetState(StateMachine *machine, int state);

int UpdatePopupManager_020c2da0(void)
{
    PopupManager *manager = data_ov093_020c5104;
    PopupStateHandler handler = data_ov093_020c3e74[func_ov093_020c3bf4(&manager->machine)];

    if (handler != NULL) {
        handler(&manager->machine);
    }
    if (data_ov093_020c5104->pendingCount > 0 && func_ov093_020c3bf4(&manager->machine) >= 0) {
        MIi_CpuClearFast(0, &data_ov093_020c5104->machine, 0x60);
        StateMachine_SetState(&data_ov093_020c5104->machine, 1);
    }
    return 0;
}
