#include "nitro/types.h"

extern int data_ov015_020812e0;
extern int FindWidgetById(int panel, int value);
extern void PlaySoundEffect(int soundId, int arg);

/* Plays a sound when the selected panel entry matches. */
void PlaySoundOnPanelEntryMatch(int selectedEntry, u32 buttonFlags) {
    int entry;

    entry = FindWidgetById(data_ov015_020812e0 + 0x160, 0x10);
    if ((entry != selectedEntry) &&
        (entry = FindWidgetById(data_ov015_020812e0 + 0x160, 0x11), entry != selectedEntry)) {
        return;
    }
    if (((buttonFlags & 0x20) == 0) && ((buttonFlags & 0x10) == 0)) {
        return;
    }
    PlaySoundEffect(2, 0);
}
