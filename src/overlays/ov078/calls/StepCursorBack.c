#include "nitro/types.h"

extern void PlaySoundEffect(int bank, int id);
extern void func_ov078_020c473c(void *menu);

typedef struct {
    u8 pad[0x5d0];
    int cursor;
} MenuState;

void StepCursorBack(MenuState *menu)
{
    PlaySoundEffect(0, 2);
    menu->cursor += 4;
    menu->cursor = menu->cursor % 5;
    func_ov078_020c473c(menu);
}
