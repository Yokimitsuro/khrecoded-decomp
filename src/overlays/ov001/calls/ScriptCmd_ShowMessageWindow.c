#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern u32 ReadSessionPackedBits(u32 id, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 flagId);
extern int IsFieldPanelShown(void);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void ShowMessageWindowByKind(u16 *text, int windowStyle);

int ScriptCmd_ShowMessageWindow(ScriptContext *context, ScriptOperand *operands)
{
    char *text;
    int windowStyle;
    u32 progress;
    u16 wideText[0x200];

    text = ByteCode_ResolveOperand(context, operands);
    windowStyle = ScriptVm_ReadOperandInt(context, operands + 1);
    if (context->isSkipping != 0) {
        return 1;
    }
    progress = ReadSessionPackedBits(0x1a00, 2);
    if ((progress == 1 || progress == 3) && func_ov001_020645c8(0x363d) == 0) {
        return 1;
    }
    if (IsFieldPanelShown() == 0) {
        return 0;
    }
    Utf8ToUcs2(text, wideText, 0x200);
    ShowMessageWindowByKind(wideText, windowStyle);
    return 1;
}
