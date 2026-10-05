#include "nitro/types.h"

typedef struct NameTable {
    u8 pad_00[0xa];
    u8 count;
    u8 pad_0b;
    char **names;
} NameTable;

typedef struct Session {
    u8 pad_0000[0x27e8];
    NameTable nameTable;
} Session;

extern Session *data_ov001_020a0480;
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void ShowFieldPopupText(u16 *text, int duration);
extern void DrawFieldHeaderText(u16 *text);

void ShowSessionNameEntry(int index) {
    u16 text[0x80];
    NameTable *table = &data_ov001_020a0480->nameTable;
    BOOL changed = FALSE;
    const char *name;
    int lastIndex = ReadSessionPackedBits(0x360d, 7) - 1;
    if (index >= 0) {
        name = table->names[index];
        if (index != lastIndex) {
            changed = TRUE;
            WriteSessionPackedBits(0x360d, 7, index + 1);
        }
    } else {
        if (lastIndex < 0) {
            return;
        }
        name = table->names[lastIndex];
    }
    if (Utf8ToUcs2(name, text, 0x80) == 0) {
        changed = FALSE;
    }
    if (changed) {
        ShowFieldPopupText(text, 2000);
    } else {
        DrawFieldHeaderText(text);
    }
}
