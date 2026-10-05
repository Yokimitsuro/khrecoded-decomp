#include "nitro/types.h"

typedef struct {
    s8 mode;
    s8 kind;
    s16 x;
    s16 y;
} StartParams;

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    s8 mode;
    u8 pad_09[0x17];
    int timer;
} MovieState;

typedef struct {
    u8 pad_00[2];
    u16 current;
    u16 saved;
} SelectionRecord;

extern MovieState *data_ov030_020bd020;
extern SelectionRecord *GetOverlaySelectionRecord(int index);
extern void ClearFieldCounters(void);

void ApplyMovieStartParams(StartParams *params)
{
    BOOL restore = TRUE;
    int i;

    if (data_ov030_020bd020->flags & 0x80) {
        restore = FALSE;
    }
    data_ov030_020bd020->x = params->x;
    data_ov030_020bd020->y = params->y;
    data_ov030_020bd020->kind = params->kind;
    data_ov030_020bd020->flags = 3;
    data_ov030_020bd020->flags |= 0x20;
    data_ov030_020bd020->mode = params->mode;
    data_ov030_020bd020->timer = 0;
    if (restore) {
        for (i = 0; i < 3; i++) {
            GetOverlaySelectionRecord(i)->current = GetOverlaySelectionRecord(i)->saved;
        }
        ClearFieldCounters();
    }
}
