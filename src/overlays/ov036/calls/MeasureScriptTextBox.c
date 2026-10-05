#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern const char *ScriptVm_ReadTableOffsetPtr(void *vm, void *operand);
extern int Utf8ToUcs2Bounded(const char *src, u16 *dst, int dstCount);
extern void func_ov036_020c2b9c(TextBoxSize *outSize, int screen, const u16 *text, int padX, int padY);

void MeasureScriptTextBox(TextBoxSize *outSize, void *vm, void *operand)
{
    TextBoxSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded(ScriptVm_ReadTableOffsetPtr(vm, operand), text, 0x200);
    func_ov036_020c2b9c(&size, 1, text, 0, 0);
    *outSize = size;
}
