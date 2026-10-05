#include "nitro/types.h"

typedef struct SoundIdTable {
    u32 ids[7];
} SoundIdTable;

typedef struct MenuScene {
    u8 pad_000[0x9b4];
    u8 selectionIndex;
    u8 pad_9b5[0xb2c - 0x9b5];
    u8 cursor[0x1278 - 0xb2c];
    s16 slotEntries[7];
} MenuScene;

extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern void SetSoundPairAndQueue(void *cursor, int value, int mode);
extern void SetSoundIdAndQueue(void *cursor, int value);
extern void QueueSoundCommandForArc(u32 seqArcNo);
extern const SoundIdTable data_ov054_020d3690;

void LoadMenuSoundArcs(MenuScene *scene)
{
    int i;
    GetOverlaySelectionRecord(scene->selectionIndex);
    SetSoundPairAndQueue(scene->cursor, 0x3e, -1);
    SetSoundIdAndQueue(scene->cursor, 0x3a);
    {
        SoundIdTable table = data_ov054_020d3690;
        for (i = 0; i < 7; i++) {
            if (scene->slotEntries[i] >= 0) {
                QueueSoundCommandForArc(table.ids[i]);
            }
        }
    }
    QueueSoundCommandForArc(0xc2);
}
