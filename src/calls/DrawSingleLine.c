#include "nitro/types.h"

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void DrawTextColored(void *context, int x, int y, int color, int param5, const void *param6);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DrawSingleLine(void *context, int x, int y, int color, int param5, u16 *text, void **cursorOut)
{
    int count = 0;
    u16 *p = text;
    u16 ch;

    if (cursorOut != 0) {
        *cursorOut = 0;
    }
    while ((ch = *p) != 0 && ch != 10) {
        p++;
        count++;
    }
    if (count != 0) {
        void *line;
        if (cursorOut != 0 && ch != 0) {
            *cursorOut = p + 1;
        }
        line = NNS_FndAllocFromDefaultExpHeapEx((count + 1) * 2, -4);
        MIi_CpuCopy16(text, line, count * 2);
        ((u16 *)line)[count] = 0;
        DrawTextColored(context, x, y, color, param5, line);
        NNSi_FndFreeFromDefaultHeap(line);
    }
}
