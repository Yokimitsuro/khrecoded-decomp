#include "nitro/types.h"

typedef struct ScriptVm ScriptVm;
typedef int (*ScriptSlotFn)(ScriptVm *vm, s32 arg);
typedef int (*ScriptCmdFn)(ScriptVm *vm, u8 *operands);

typedef struct ScriptSlot {
    ScriptSlotFn fn;
    s32 arg;
} ScriptSlot;

typedef struct ScriptFrame {
    u8 pad_00[4];
    s32 size;
    u8 pad_08[8];
    u8 *cursor;
    u8 pad_14[4];
    ScriptSlot slots[11];
} ScriptFrame;

typedef struct ScriptCmdHandler {
    ScriptCmdFn run;
    ScriptSlotFn resume;
} ScriptCmdHandler;

struct ScriptVm {
    s32 stackUsed;
    ScriptFrame frames[4];
    s32 depth;
    u8 pad_1c8[4];
    s32 status;
    u8 pad_1d0[0x624 - 0x1d0];
    u8 *skipTarget;
    s32 skipRequested;
    s32 skipping;
};

extern void ScriptVm_FinishSkip(ScriptVm *vm);
extern ScriptCmdHandler *data_02055e04[];

int ScriptVm_RunFrame(ScriptVm *vm)
{
    ScriptFrame *frame = &vm->frames[vm->depth];
    ScriptCmdHandler *table;
    ScriptCmdHandler *handler;
    u8 *cmd;
    int result;
    int i;
    u8 field;

    if (vm->skipRequested != 0 && vm->skipping == 0 && vm->skipTarget != NULL) {
        ScriptVm_FinishSkip(vm);
    }

    for (i = 0; i < 10; i++) {
        if (frame->slots[i + 1].fn != NULL && frame->slots[i + 1].fn(vm, frame->slots[i + 1].arg) != 0) {
            frame->slots[i + 1].fn = NULL;
            frame->slots[i + 1].arg = 0;
        }
    }

    if (frame->slots[0].fn != NULL) {
        switch (frame->slots[0].fn(vm, frame->slots[0].arg)) {
        case 1:
            cmd = frame->cursor;
            frame->cursor = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
            break;
        case 0:
            return 1;
        case 2:
            frame->slots[0].fn = NULL;
            break;
        }
    }

next:
    frame = &vm->frames[vm->depth];
    cmd = frame->cursor;
    if (vm->skipping != 0 && cmd >= vm->skipTarget) {
        return 0;
    }
    table = data_02055e04[cmd[0]];
    if (table != NULL) {
        handler = &table[cmd[1]];
    } else {
        frame->slots[0].fn = NULL;
        frame->cursor = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
        goto next;
    }
    if (((*(u16 *)(cmd + 2) >> 11) & 0x1f) != 0 && vm->skipping == 0) {
        result = handler->run(vm, cmd + 4);
        field = (*(u16 *)(cmd + 2) >> 11) & 0x1f;
        if (result == 0) {
            frame->slots[field].fn = handler->resume;
            frame->slots[field].arg = frame->slots[0].arg;
        } else {
            frame->slots[field].fn = NULL;
            frame->slots[field].arg = 0;
        }
        frame->slots[0].fn = NULL;
        frame->cursor = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
        goto next;
    }
    if (handler->run == NULL) {
        goto next;
    }
    switch (handler->run(vm, cmd + 4)) {
    case 0:
        frame->slots[0].fn = handler->resume;
        return 1;
    case 1:
        frame->slots[0].fn = NULL;
        frame->cursor = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
        goto next;
    case 2:
        frame->slots[0].fn = NULL;
        goto next;
    case 3:
        return 0;
    case 4:
        if (vm->depth > 0) {
            vm->stackUsed -= frame->size;
            vm->depth--;
            frame = &vm->frames[vm->depth];
            frame->slots[0].fn = NULL;
            frame->cursor += (*(u16 *)(frame->cursor + 2) & 0x7ff) << 2;
            goto next;
        }
        vm->status = 2;
        return 0;
    case 5:
        goto next;
    case 6:
        frame->cursor = cmd + ((*(u16 *)(cmd + 2) & 0x7ff) << 2);
        return 1;
    default:
        goto next;
    }
}
