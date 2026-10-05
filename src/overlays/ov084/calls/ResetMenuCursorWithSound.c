#include "nitro/types.h"

extern void StartSubScene(int a, int b, int c);
extern void PlaySoundEffect(int channel, int id);

void ResetMenuCursorWithSound(void)
{
    StartSubScene(-1, -1, 1);
    PlaySoundEffect(0, 3);
}
