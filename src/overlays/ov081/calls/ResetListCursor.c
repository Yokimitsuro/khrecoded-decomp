#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x63c6];
    s8 cursor;
} Ov081State;

extern Ov081State *data_ov081_020c5da0;
extern void SkipToUnlockedListEntry(Ov081State *state, BOOL forward);
extern void func_ov081_020c5660(void *obj);
extern void func_ov081_020c4e08(void *obj);
extern void *func_ov081_020c544c(void);
extern void DrawListTitle(Ov081State *state, void *list);

void ResetListCursor(void)
{
    Ov081State *state;

    data_ov081_020c5da0->cursor = 0;
    SkipToUnlockedListEntry(data_ov081_020c5da0, TRUE);
    state = data_ov081_020c5da0;
    DrawListTitle(state, func_ov081_020c544c());
    func_ov081_020c5660(state);
    func_ov081_020c4e08(data_ov081_020c5da0);
}
