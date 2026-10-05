#include "nitro/types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    s8 level;
    u8 visible;
    s16 count;
    u8 pad_28[4];
} MarkerRequest;

typedef struct {
    int rates[4];
} GaugeRates;

typedef struct {
    u8 pad_00[6];
    u16 triggered;
} StepTimer;

typedef struct {
    u8 pad_00[2];
    u16 gauge;
} ActorInfo;

typedef struct {
    u8 pad_0000[0x1d4];
    ActorInfo *info;
    u8 pad_01d8[0x9b4 - 0x1d8];
    u8 player;
    u8 pad_09b5[3];
    int kind;
    u8 pad_09bc[4];
    int stageType;
    u8 pad_09c4[0x9ec - 0x9c4];
    int frameStep;
    u8 pad_09f0[0x1037 - 0x9f0];
    s8 palette;
    u8 pad_1038[0x10d4 - 0x1038];
    StepTimer gaugeTimer;
    StepTimer healTimer;
} Actor;

extern const GaugeRates data_ov052_020d210c;
extern s32 func_ov001_02063a38(void);
extern int func_ov001_02064784(void);
extern u32 func_ov001_02064490(void);
extern s32 GetClampedPaletteSlot(void);
extern int _s32_div_f(int value, int scale);
extern int AdvanceTimerWithCarry(StepTimer *timer, int step, int amount);
extern int AdvanceStepTimer(StepTimer *timer, int step, int value);
extern void func_ov001_02073074(int delta, BOOL loadNow);
extern void ClearHandleActiveFlags(void);
extern u32 func_ov001_0207b588(s32 index);
extern void MarkTaggedEntry(u32 id);
extern BOOL IsFieldFlag16Set(void);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern void PlaySoundChecked(void *ptr, int arg);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void ApplyScaledHealthDelta(Actor *actor, s32 amount, BOOL force);

void UpdateDriveGaugeCharge(Actor *actor)
{
    BOOL charging = TRUE;
    int i;
    int level;
    int heal;
    GaugeRates rates;
    MarkerRequest request;

    if (actor->kind != 0 || actor->info->gauge == 0 || func_ov001_02063a38() == 6) {
        return;
    }
    if (actor->stageType == 0x18) {
        charging = FALSE;
    }
    if (func_ov001_02064784() == 5 && actor->stageType == 0x1f) {
        charging = FALSE;
    }
    if (charging) {
        StepTimer *timer = &actor->gaugeTimer;
        int rate;
        int amount;
        rates = data_ov052_020d210c;
        rate = _s32_div_f(rates.rates[GetClampedPaletteSlot()], 100);
        amount = (int)(((s64)rate * 0x400 + 0x800) >> 12);
        if (!func_ov001_02064490()) {
            int gain = AdvanceTimerWithCarry(timer, actor->frameStep, amount);
            if (gain > 0) {
                func_ov001_02073074(-gain, FALSE);
                timer->triggered = 1;
            }
        }
    }
    level = GetClampedPaletteSlot();
    ClearHandleActiveFlags();
    for (i = 0; i < 4; i++) {
        u32 entry = func_ov001_0207b588(i);
        if (i > level) {
            break;
        }
        MarkTaggedEntry(entry);
    }
    if (IsFieldFlag16Set()) {
        level = 4;
    }
    if (actor->palette < level && level > 0) {
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.visible = 1;
        request.count = 1;
        request.angle = GetLinkedAngleOffset(actor) + 0x8000;
        request.level = level - 1;
        if (level != 4) {
            PlaySoundChecked(NULL, 0x43);
        } else {
            PlaySoundChecked(NULL, 0x44);
        }
        func_ov021_020a8cc0(&request, func_ov001_0206db8c(6));
    }
    actor->palette = level;
    if (IsPlayerEntryFlagSet(actor->player, 0x44)) {
        heal = AdvanceStepTimer(&actor->healTimer, actor->frameStep, 0x6400);
        if (heal > 0) {
            if (heal < 0x1000) {
                heal = 0x1000;
            }
            ApplyScaledHealthDelta(actor, heal, FALSE);
        }
    }
}
