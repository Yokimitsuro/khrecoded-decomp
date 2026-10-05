#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x63c6];
    s8 cursor;
} Ov081State;

typedef struct {
    u8 kind;
    u8 count;
} EntryList;

extern Ov081State *data_ov081_020c5da0;
extern EntryList *func_ov081_020c544c(void);
extern void SkipToUnlockedListEntry(Ov081State *state, BOOL forward);
extern void DrawListTitle(Ov081State *state, EntryList *list);
extern void func_ov081_020c5660(void *obj);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ScrollListForward(Ov081State *state)
{
    EntryList *list = func_ov081_020c544c();
    Ov081State *current;
    s8 previous;

    if (list->kind == 1) {
        previous = state->cursor;
        state->cursor = (previous + 1) % list->count;
        SkipToUnlockedListEntry(state, TRUE);
        if (state->cursor != previous) {
            current = data_ov081_020c5da0;
            DrawListTitle(current, func_ov081_020c544c());
            func_ov081_020c5660(current);
            PlaySoundEffect(0, 2);
        }
    }
}
