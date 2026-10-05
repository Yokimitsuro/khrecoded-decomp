#include "nitro/types.h"

typedef struct TextBoxSize {
    s32 width;
    s32 height;
} TextBoxSize;

extern int ByteCode_ResolveOperand(int scriptCtx, unsigned short *operand);
extern int Utf8ToUcs2Bounded(const char *src, u16 *dst, int dstCount);
extern void func_ov036_020c2b9c(TextBoxSize *outSize, int screen, const u16 *text, int padX, int padY);

void MeasureScriptOperandText(TextBoxSize *outSize, int scriptCtx, unsigned short *operand)
{
    TextBoxSize size;
    u16 text[0x200];

    Utf8ToUcs2Bounded((const char *)ByteCode_ResolveOperand(scriptCtx, operand), text, 0x200);
    func_ov036_020c2b9c(&size, 0, text, 0, 0);
    *outSize = size;
}
