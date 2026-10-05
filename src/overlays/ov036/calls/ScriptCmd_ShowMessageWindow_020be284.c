#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

extern int ByteCode_ResolveOperand(ScriptVm *vm, unsigned short *operand);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void Utf8ToUcs2(const char *src, u16 *dst, int dstCount);
extern BOOL OpenMessageTextWindow(const u16 *text);

BOOL ScriptCmd_ShowMessageWindow_020be284(ScriptVm *vm, unsigned short *operand)
{
    u16 text[0x100];
    const char *message = (const char *)ByteCode_ResolveOperand(vm, operand);
    u32 mode;

    if (vm->skipWait != 0) {
        return TRUE;
    }
    mode = ReadSessionPackedBits(0x1a00, 2);
    if (mode == 1 || mode == 3) {
        return TRUE;
    }
    Utf8ToUcs2(message, text, 0x100);
    OpenMessageTextWindow(text);
    return TRUE;
}
