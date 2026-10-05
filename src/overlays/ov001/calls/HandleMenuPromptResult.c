#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 3;
    u32 bit3 : 1;
    u32 bit4 : 1;
    u32 unk_5 : 6;
    u32 bit11 : 1;
    u32 unk_12 : 1;
    u32 bit13 : 1;
    u32 bit14 : 1;
    u32 unk_15 : 17;
} SessionFlags;

typedef struct MenuControl {
    u8 pad_00[0x8];
    s8 state;
    u8 pad_09[0x27];
    int (*pollSelection)(void);
} MenuControl;

typedef struct Session {
    u8 pad_0000[0x20e];
    s16 unk_20E;
    u8 pad_0210[0x4];
    SessionFlags flags;
    u8 pad_0218[0x3c];
    s8 unk_254;
    u8 pad_0255[0x27ec - 0x255];
    s32 unk_27EC;
    u8 pad_27F0[0x10];
    MenuControl menu;
} Session;

extern Session *data_ov001_020a0480;
extern int func_ov001_020644b0(void);
extern void SetPendingFieldValue(int mode);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern void ConfigureFieldTracks(int areaId, int roomId, int entranceId, int transitionFlags);
extern void func_ov001_020645dc(u32 eventId);
extern void OpenFieldMenuMode(int mode);

int HandleMenuPromptResult(void)
{
    Session *session = data_ov001_020a0480;
    int selection = 0;
    int result = -1;
    MenuControl *menu = &session->menu;
    int slotIndex;

    if (menu->pollSelection != NULL) {
        selection = menu->pollSelection();
    }
    switch (menu->state) {
    case 5:
        if (func_ov001_020644b0() == 899) {
            SetPendingFieldValue(0);
        } else if (session->flags.bit13) {
            if (session->unk_27EC == 3 && selection != 0) {
                slotIndex = ReadGlobalPackedBits(0x1a00, 2);
                ConfigureFieldTracks(ReadGlobalPackedBits(slotIndex * 0xf00 + 0x330b, 10),
                                    ReadGlobalPackedBits(slotIndex * 0xf00 + 0x3315, 10), 2, slotIndex);
                data_ov001_020a0480->unk_254 = -1;
            } else if (session->unk_27EC != 7) {
                session->unk_20E = -3;
            }
        } else {
            func_ov001_020645dc(0x1a06);
            session->flags.bit3 = TRUE;
        }
        session->flags.bit14 = FALSE;
        result = 11;
        break;
    case 11:
        func_ov001_020645dc(0x1a06);
        result = 11;
        break;
    case 9:
        switch (selection) {
        case 0:
            if (session->flags.bit11) {
                SetPendingFieldValue(2);
            } else {
                func_ov001_020645dc(0x1a06);
                session->flags.bit4 = TRUE;
                session->flags.bit13 = FALSE;
                data_ov001_020a0480->unk_254 = -1;
            }
            break;
        case 1:
            OpenFieldMenuMode(3);
            session->flags.bit13 = TRUE;
            break;
        case 2:
            OpenFieldMenuMode(0);
            session->flags.bit13 = TRUE;
            break;
        case 3:
            OpenFieldMenuMode(4);
            session->flags.bit13 = TRUE;
            break;
        }
        result = 11;
        break;
    case 12:
        OpenFieldMenuMode(9);
        result = 11;
        break;
    }
    return result;
}
