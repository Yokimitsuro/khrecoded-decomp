#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct ScriptVm ScriptVm;
typedef int (*ScriptSlotFn)(ScriptVm *vm, s32 arg);

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

typedef struct ScriptDisplay {
    u8 pad_00[0x1c];
    s32 brightness;
    u8 pad_20[0x10];
    s32 secondaryBrightness;
    u8 pad_34[0xc8 - 0x34];
    u8 scratch[0x100];
} ScriptDisplay;

struct ScriptVm {
    s32 stackUsed;
    ScriptFrame frames[4];
    s32 depth;
    ScriptDisplay *display;
    s32 status;
    u8 pad_1d0[0x620 - 0x1d0];
    s32 skipDepth;
    u8 *skipTarget;
    s32 skipRequested;
    s32 skipping;
};

typedef struct ActorInfo {
    u8 pad_00[0x7d];
    u8 kind;
} ActorInfo;

typedef struct ActorNode {
    u8 pad_00[4];
    struct ActorNode *next;
    ActorInfo *info;
} ActorNode;

typedef struct {
    u8 pad_00[0x10];
    s32 busy;
} ScriptGlobals;

extern ScriptGlobals gScriptState;

extern int func_ov001_02063838(void);
extern ActorNode *func_ov001_0207f0b4(void);
extern void func_ov001_020814f8(ActorNode *node);
extern void func_ov001_0207a820(void);
extern void func_ov036_020c3368(void);
extern void HideAllOamEntries(int value);
extern void func_ov001_02063c78(int value);
extern void func_ov001_02088aa4(void);
extern int ScriptVm_RunFrame(ScriptVm *vm);
extern void G2x_SetBlendBrightness_(u32 reg, int planes, int value);
extern void SetBrightnessAndSyncMain(s32 brightness);
extern void SetSecondaryBrightness(s32 brightness);
extern int ScriptCmd_TurnHandler(ScriptVm *vm, s32 arg);
extern void func_02026974(ScriptVm *vm, s32 index);
extern void MIi_CpuClear32(u32 value, void *dest, u32 size);

void ScriptVm_FinishSkip(ScriptVm *vm)
{
    ScriptFrame *frame = &vm->frames[vm->depth];
    ActorNode *node;
    int i;
    int depth;

    if (gScriptState.busy == 0) {
        vm->skipping = 1;
        vm->status = -1;

        if (func_ov001_02063838()) {
            for (node = func_ov001_0207f0b4(); node != NULL; node = node->next) {
                if (node->info->kind == 1) {
                    func_ov001_020814f8(node);
                }
            }
            func_ov001_0207a820();
        } else {
            func_ov036_020c3368();
            HideAllOamEntries(1);
            func_ov001_02063c78(1);
        }

        while (ScriptVm_RunFrame(vm)) {
            func_ov001_02063c78(1);
            if (func_ov001_02063838()) {
                func_ov001_02088aa4();
            }
        }

        if (func_ov001_02063838()) {
            u32 subPlanes;

            G2x_SetBlendBrightness_(REG_DISPCNT_ADDR + 0x50, 1, 0);
            subPlanes = (*(vu32 *)REG_DB_DISPCNT_ADDR & 0x1f00) >> 8;
            G2x_SetBlendBrightness_(REG_DB_DISPCNT_ADDR + 0x50, subPlanes, 0);
        }

        SetBrightnessAndSyncMain(vm->display->brightness);
        if (vm->display->brightness != 0) {
            SetSecondaryBrightness(vm->display->secondaryBrightness);
        }
    }

    for (i = 0; i < 10; i++) {
        if (frame->slots[i + 1].fn != NULL) {
            if (frame->slots[i + 1].fn == ScriptCmd_TurnHandler) {
                func_02026974(vm, frame->slots[i + 1].arg);
            }
            frame->slots[i + 1].fn = NULL;
            frame->slots[i + 1].arg = 0;
        }
    }

    if (frame->slots[0].fn != NULL) {
        if (frame->slots[0].fn == ScriptCmd_TurnHandler) {
            func_02026974(vm, frame->slots[0].arg);
        }
        frame->slots[0].fn = NULL;
    }

    for (depth = vm->depth; depth > vm->skipDepth; depth--) {
        vm->stackUsed -= vm->frames[depth].size;
    }

    vm->depth = vm->skipDepth;
    vm->frames[vm->depth].cursor = vm->skipTarget;
    vm->skipRequested = 0;
    vm->skipping = 0;
    vm->skipTarget = NULL;
    MIi_CpuClear32(0, vm->display->scratch, sizeof(vm->display->scratch));
}
