#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x20e];
    s16 cursor;
    u8 pad_0210[0x214 - 0x210];
    u32 flags;
    u8 pad_0218[0x2738 - 0x218];
    s8 menuLock;
    u8 pad_2739[0x2744 - 0x2739];
    s8 busyCount;
    u8 pad_2745[0x27ec - 0x2745];
    u32 menuMode;
    u8 pad_27f0[0x28a4 - 0x27f0];
    u8 menuRequested;
} FieldState;

extern FieldState *data_ov001_020a0480;

extern void func_ov001_0206e53c(int value);
extern void func_ov001_0206e444(int value);
extern void SetMenuHighlight(int value);

void OpenFieldMenuMode(u32 kind) {
    FieldState *field = data_ov001_020a0480;

    if (field->busyCount > 0) {
        return;
    }
    switch (kind) {
    case 0:
        field->menuMode = 0;
        break;
    case 1:
        field->menuMode = 1;
        break;
    case 2:
        field->menuMode = 2;
        break;
    case 3:
        field->menuMode = 3;
        break;
    case 4:
        field->menuMode = 7;
        break;
    case 5:
        field->menuMode = 5;
        break;
    case 6:
        field->menuMode = 6;
        break;
    case 7:
        if (field->menuLock & 0x80) {
            return;
        }
        field->menuMode = 0;
        break;
    case 8:
        field->menuMode = 0x80000005;
        break;
    case 9:
        field->menuMode = 0x40000002;
        break;
    }
    field->flags |= 0x1000;
    field->cursor = -2;
    field->menuRequested = 1;
    func_ov001_0206e53c(1);
    func_ov001_0206e444(1);
    SetMenuHighlight(1);
}
