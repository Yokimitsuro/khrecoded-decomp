#include "nitro/types.h"

typedef struct GaugeAnim {
    u64 startTick;
    s32 rate;
    s32 elapsed;
    s32 active;
    s32 frame;
} GaugeAnim;

typedef struct GaugeSlot {
    u16 maximum;
    u16 current;
    u16 pad_04;
} GaugeSlot;

typedef struct GaugeScale {
    s32 scale;
    u8 pad_04[8];
} GaugeScale;

typedef struct GaugeMenu {
    void *contexts[10];
    s32 soundPlaying;
    u8 pad_2c[0x6c - 0x2c];
    GaugeAnim anims[3];
    GaugeSlot slots[10];
    u8 pad_f0[2];
    u16 primaryState;
} GaugeMenu;

extern GaugeMenu *data_ov001_020a04cc;
extern GaugeScale data_ov001_0209edf8[];
extern void DrawShortLayoutRow(void *context, int index, int mode);
extern void func_ov001_02073870(void *context, int index, int mode);
extern u64 OS_GetTick(void);
extern void AdvanceGaugeSlot(int index, GaugeAnim *anim);
extern void RunMenuEntryCallbacks(void *context, int menu, int count, void (*callback)(void *context, int index, int mode), int mode);
extern void UploadScreenSlotBlock(int index, int mode);
extern BOOL IsFieldPanelHidden(void);
extern BOOL IsFirstEntryFlagSet(void);
extern u32 func_ov001_02064490(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void StopSeqArcOrDefault(int seqArcNo, int index, int fade);

void SetMenuGaugeActive(int index, BOOL enable) {
    GaugeMenu *menu = data_ov001_020a04cc;
    GaugeAnim *anim = &menu->anims[index];
    void (*callback)(void *context, int index, int mode);
    u16 state;
    u16 current;

    if (index == 0) {
        callback = DrawShortLayoutRow;
        state = menu->primaryState;
        if (state == 0 && menu->slots[0].current != 0) {
            state = 1;
        }
    } else {
        callback = func_ov001_02073870;
        current = menu->slots[index].current;
        state = (current * data_ov001_0209edf8[index].scale) / menu->slots[index].maximum;
        if (state == 0 && current != 0) {
            state = 1;
        }
    }
    if (enable) {
        anim->active = 1;
        anim->frame = 0;
        anim->rate = 0x3fec4;
        anim->elapsed = 0;
        anim->startTick = OS_GetTick();
        AdvanceGaugeSlot(index, anim);
        UploadScreenSlotBlock(index, 2);
    } else {
        anim->active = 0;
        RunMenuEntryCallbacks(menu->contexts[index], index, state, callback, menu->slots[index].current == 0);
        UploadScreenSlotBlock(index, 0);
    }
    if (index == 0) {
        if (enable) {
            if (menu->soundPlaying == 0 && IsFieldPanelHidden() && !IsFirstEntryFlagSet() && !func_ov001_02064490()) {
                PlaySoundEffect(0, 0xe);
                menu->soundPlaying = 1;
            }
        } else if (menu->soundPlaying != 0) {
            StopSeqArcOrDefault(0, 0xe, 0);
            menu->soundPlaying = 0;
        }
    }
}
