#include "nitro/types.h"

typedef struct {
    char tags[9][3];
} SlotTagTable;

typedef struct {
    u8 pad_0000[0xcab4];
    void *slots[4];
} Ov039State;

extern const SlotTagTable data_ov039_020be784;
extern const char sOv039_UiMenuFormatSP2_020be828[];
extern const char sOv039_UiMenuLanguageFormatSP2_020be838[];
extern void *OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadSlotImagePair(Ov039State *state, int slot, int kind)
{
    SlotTagTable table = data_ov039_020be784;
    char path[64];

    OS_SNPrintf(path, sizeof(path), sOv039_UiMenuFormatSP2_020be828, table.tags[kind + 1]);
    state->slots[slot] = Msg_OpenContainerAndReadHeader(path, 14, FALSE);
    OS_SNPrintf(path, sizeof(path), sOv039_UiMenuLanguageFormatSP2_020be838, table.tags[kind + 1]);
    state->slots[slot + 1] = Msg_OpenContainerAndReadHeader(path, 14, FALSE);
}
