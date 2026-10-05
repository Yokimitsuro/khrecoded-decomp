#include "nitro/types.h"

typedef struct RecordEntry {
    u8 pad_00[0x40];
    int nameId;
} RecordEntry;

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[2];
    u8 flags;
    u8 pad_04[0x109c - 4];
    u16 message[0x20];
    u8 pad_10dc[0x10e4 - 0x10dc];
    int messageKind[2];
    u8 pad_10ec[0x11cc - 0x10ec];
    u8 strings[1];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern void SetStatusHeaderText(const u16 *shortText, const u16 *longText);
extern RecordEntry *GetRecordSlotPair0Entry(s32 index);
extern u16 *func_ov027_020ba300(void *messages, int index, u16 *buffer, int size, ...);

void SetStatusHeaderMessage(const u16 *shortText, const u16 *longText, int kind, int value)
{
    MenuSharedState *state = func_ov039_020bc650();
    int page;

    if (state->flags & 2) {
        page = 1;
    } else {
        page = 0;
    }
    SetStatusHeaderText(shortText, longText);
    if (shortText != NULL && longText != NULL) {
        switch (kind) {
        case 1:
            func_ov027_020ba300(state->strings, 0x27, state->message, 0x20, value);
            break;
        case 2:
            func_ov027_020ba300(state->strings, 0x28, state->message, 0x20,
                                GetRecordSlotPair0Entry(0x160)->nameId, value);
            break;
        case 3:
            func_ov027_020ba300(state->strings, 0x28, state->message, 0x20,
                                GetRecordSlotPair0Entry(0x161)->nameId, value);
            break;
        default:
            state->message[0] = 0;
            break;
        }
        state->messageKind[page] = kind;
    } else if (kind == 4) {
        state->messageKind[page] = kind;
    }
}
