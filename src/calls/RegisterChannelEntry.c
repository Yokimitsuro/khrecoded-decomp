#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s32 index;
    u32 value;
} ActiveEntryState;

typedef struct ChannelSlot {
    u32 inUse;
    char name[0x10];
    u32 kind;
    struct ChannelSlot *next;
    struct ChannelSlot *prev;
} ChannelSlot;

extern volatile u32 data_020569d8[];
extern ChannelSlot data_020569e0[4][4];
extern volatile ActiveEntryState gVBlankCallbackState;

extern char *strncpy(char *dst, const char *src, unsigned n);
extern void AppendNodeToListTail(u32 *node, u32 *newNode);
extern unsigned OS_DisableIrqMask(unsigned mask);
extern unsigned OS_EnableIrqMask(unsigned mask);

void RegisterChannelEntry(u32 arg0, const char *name, int kind, int channel)
{
    u32 head = data_020569d8[channel];
    ChannelSlot *slot = data_020569e0[channel];
    int i = 0;

    do {
        if (slot->inUse == 0) {
            break;
        }
        i++;
        slot++;
    } while (i < 4);

    strncpy(slot->name, name, 0x10);
    slot->inUse = 1;
    slot->kind = kind;
    slot->next = NULL;

    OS_DisableIrqMask(1);
    AppendNodeToListTail((u32 *)head, (u32 *)slot);

    if (data_020569d8[channel] == 0) {
        if (gVBlankCallbackState.index == channel) {
            gVBlankCallbackState.value = (u32)slot;
        }
        data_020569d8[channel] = (u32)slot;
    }
    OS_EnableIrqMask(1);
}
