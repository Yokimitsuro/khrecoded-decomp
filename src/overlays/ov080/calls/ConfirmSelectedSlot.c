#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 unk_08;
    u8 pad_09[2];
    u8 unk_0B;
    u8 pad_0C[0x6c];
    SaveSlot slots[2];
} SaveSelectScreen;

extern u32 func_ov039_020bc934(void);
extern int GetCurrentSceneId(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ConfirmSelectedSlot(SaveSelectScreen *screen)
{
    if (func_ov039_020bc934() == 3 && GetCurrentSceneId() == 1 && screen->step == 0) {
        if (screen->slots[screen->slotIndex].status != 0) {
            screen->step = 1;
            screen->unk_0B = 1;
            screen->unk_08 = 1;
            screen->needsRedraw = 1;
            PlaySoundEffect(0, 1);
            return;
        }
        PlaySoundEffect(0, 4);
    }
}
