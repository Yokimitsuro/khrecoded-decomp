#include "nitro/types.h"

typedef struct MenuMachine {
    u8 pad_000[0x13c];
    u16 flags;
    u8 pad_13e[2];
    int state;
    int result;
} MenuMachine;

typedef int (*MenuStateFunc)(void);

extern MenuMachine *data_ov040_020be280;
extern MenuStateFunc gAreaSceneStateHandlers[];

int RunMenuStateMachine(void)
{
    MenuMachine *machine = data_ov040_020be280;
    int *state = &machine->state;

    do {
        int next;

        data_ov040_020be280->flags &= 0x7fff;
        next = gAreaSceneStateHandlers[machine->state]();
        if (next >= 0) {
            *state = next;
        }
    } while (data_ov040_020be280->flags & 0x8000);
    if (machine->flags & 2) {
        return machine->result;
    }
    return 0;
}

