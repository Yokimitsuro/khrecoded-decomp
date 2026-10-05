#include "nitro/types.h"

extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern int advanceTextStringCursor(int textBytes, int *byteCursor);
extern char *strcpy(char *dst, const char *src);
extern void strncpy(char *dst, const char *src, int n);

BOOL SplitTextAtLineBreak(char *text, char *dest)
{
    int cursor;
    char lineBuffer[256];

    cursor = 0;
    MIi_CpuClear32(0, dest, 0x100);
    if (advanceTextStringCursor((int)text, &cursor) != 0) {
        MIi_CpuClear32(0, lineBuffer, 0x100);
        strcpy(dest, text + cursor);
        strncpy(lineBuffer, text, cursor + -2);
        strcpy(text, lineBuffer);
        return TRUE;
    }
    return FALSE;
}
