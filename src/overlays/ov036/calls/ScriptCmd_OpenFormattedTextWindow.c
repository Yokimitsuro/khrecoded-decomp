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

typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern const char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern u16 *func_ov036_020be2f4(const u16 *format, u16 *dest, u32 destLength, ...);
extern BOOL GetPanelCursorOverride(s32 *outSelection, ScreenPoint *outPosition);
extern void AccumulateTextBoxScroll(ScriptContext *context, ScriptOperand *textOperand, int windowId, s32 selection, ScreenPoint *position);
extern BOOL OpenTextWindowWithText(int windowId, s32 selection, ScreenPoint *position, int style, const u16 *text);

int ScriptCmd_OpenFormattedTextWindow(ScriptContext *context, ScriptOperand *operands)
{
    ScriptOperand *op = operands;
    ScriptOperand *textOperand;
    const char *utf8;
    int windowId;
    ScreenPoint position;
    s32 selection;
    int style;
    int value;
    u16 format[0x100];
    u16 text[0x100];

    ScriptVm_ReadOperandInt(context, op++);
    textOperand = op;
    utf8 = ByteCode_ResolveOperand(context, op++);
    windowId = ScriptVm_ReadOperandInt(context, op++);
    selection = ScriptVm_ReadOperandInt(context, op++);
    style = ScriptVm_ReadOperandInt(context, op++);
    if (context->isSkipping != 0) {
        return 1;
    }
    position.x = ScriptVm_ReadOperandInt(context, op++);
    position.y = ScriptVm_ReadOperandInt(context, op++);
    value = ScriptVm_ReadOperandInt(context, op++);
    Utf8ToUcs2(utf8, format, 0x100);
    func_ov036_020be2f4(format, text, 0x100, value);
    if (!GetPanelCursorOverride(&selection, &position)) {
        AccumulateTextBoxScroll(context, textOperand, windowId, selection, &position);
    }
    OpenTextWindowWithText(windowId, selection, &position, style, text);
    return 1;
}
