#include "nitro/types.h"

#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)

typedef struct PanelState {
    u8 pad_00[0xe4];
    int sequenceStep;
} PanelState;

extern PanelState *data_ov015_0207e960;
extern BOOL UpdateMenuTouch(void);
extern int func_ov002_020632ac(void);
extern BOOL IsButtonBPressed(void);
extern u32 GetMenuCursorHeld(u32 *out);
extern u32 GetMenuCursorTouch(u32 *out);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov002_020620fc(int selector);
extern void func_ov015_02070af8(char nextState);

void UpdatePanelConfirmSequence(void)
{
    BOOL busy = UpdateMenuTouch();

    switch (data_ov015_0207e960->sequenceStep) {
    case 0:
        data_ov015_0207e960->sequenceStep = 5;
        break;
    case 5:
        if (!func_ov002_020632ac() && !IsButtonBPressed() && !GetMenuCursorHeld(NULL)) {
            break;
        }
        if (func_ov002_020632ac() || GetMenuCursorTouch(NULL)) {
            PlaySoundEffect(2, 1);
        } else if (IsButtonBPressed()) {
            PlaySoundEffect(2, 2);
        }
        func_ov002_020620fc(0);
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1e00;
        data_ov015_0207e960->sequenceStep = 10;
        break;
    case 10:
        if (!busy) {
            data_ov015_0207e960->sequenceStep = 20;
        }
        break;
    case 20:
        func_ov015_02070af8(1);
        break;
    }
}
