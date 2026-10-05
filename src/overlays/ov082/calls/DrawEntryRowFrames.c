#include "nitro/types.h"

typedef struct EntryList {
    u8 kind;
} EntryList;

typedef struct Ov081State {
    u8 pad_00[0x63c4];
    u8 shownCount;
} Ov081State;

typedef struct Ov082State {
    u8 pad_0000[4];
    s16 scrollTop;
    u8 pad_0006[0x3714 - 0x6];
    void *entryFrame;
    u8 pad_3718[8];
    void *headerFrame;
} Ov082State;

extern Ov081State *func_ov081_020c5bf8(void);
extern EntryList *GetSlotEntry(int slot);
extern void *G2S_GetBG2ScrPtr(void);
extern void NNS_G2dBGLoadScreenRect(void *pScreenDst, const void *pScreenData, int srcX, int srcY, int dstX,
                                             int dstY, int dstW, int dstH, int width, int height);

void DrawEntryRowFrames(Ov082State *state)
{
    int i;
    int count = func_ov081_020c5bf8()->shownCount;
    EntryList *list;
    void **frame;

    for (i = 0; i < count; i++) {
        list = GetSlotEntry(state->scrollTop + i);
        frame = &state->headerFrame;
        if (list->kind != 2) {
            frame = &state->entryFrame;
        }
        NNS_G2dBGLoadScreenRect(G2S_GetBG2ScrPtr(), *frame, 0, 0, 2, i * 2 + 4, 0x20, 0x18, 0x1c, 2);
    }
}
