#include "nitro/types.h"

typedef struct FadeEntry {
    s8 material;
    s8 target;
    s8 value;
    u8 unknown_03;
} FadeEntry;

typedef struct FadeWork {
    u8 unknown_000[0x109];
    s8 current;
    s8 count;
    u8 active;
    FadeEntry *entries;
} FadeWork;

extern FadeWork *data_ov035_020bc504;
extern const s8 data_ov035_020bc40c[4];
extern int func_ov035_020bae94(void);
extern void SetMovieSlotFlags(int index, int mode);
extern int GetMovieEntryKind(int index);
extern void func_ov035_020bb468(int index);
extern void AdvanceAnimationTracks(FadeWork *work, int frames);

void UpdateMaterialFades(int selection, int frames) {
    FadeWork *work = data_ov035_020bc504;
    int i;

    if (work->active == 0) {
        return;
    }
    if (func_ov035_020bae94() == 0) {
        int previous = work->current;
        if (previous != selection) {
            if (previous >= 0) {
                SetMovieSlotFlags(previous, 0);
            }
            work->current = selection;
        }
        if (selection >= 0) {
            u8 kind = GetMovieEntryKind(work->current);
            if (kind <= 3) {
                SetMovieSlotFlags(selection, data_ov035_020bc40c[kind]);
            }
        }
        for (i = 0; i < work->count; i++) {
            FadeEntry *entry = &work->entries[i];
            if (entry->value > entry->target) {
                entry->value -= 4;
                if (entry->value < entry->target) {
                    entry->value = entry->target;
                }
                func_ov035_020bb468(i);
            } else if (entry->value < entry->target) {
                entry->value += 4;
                if (entry->value > entry->target) {
                    entry->value = entry->target;
                }
                func_ov035_020bb468(i);
            }
        }
    }
    AdvanceAnimationTracks(work, frames);
}
