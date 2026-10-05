#include "nitro/types.h"

typedef struct Owner Owner;

typedef struct {
    int state;
    u8 timer[0x7c - 4];
    int restartPending;
} StateBlock;

struct Owner {
    u8 pad[0x550];
    StateBlock block;
};

typedef void (*StateHandler)(Owner *owner);

extern StateHandler gHudSlideStateHandlers[];
extern u32 func_ov001_02064490(void);
extern void func_02052570(void *timer);

void RunOwnerStateMachine(Owner *owner) {
    StateBlock *block = &owner->block;
    if (func_ov001_02064490() == 0 && block->restartPending != 0) {
        func_02052570(block->timer);
        block->state = 1;
        block->restartPending = 0;
    }
    if (gHudSlideStateHandlers[block->state] != NULL) {
        gHudSlideStateHandlers[block->state](owner);
    }
}
