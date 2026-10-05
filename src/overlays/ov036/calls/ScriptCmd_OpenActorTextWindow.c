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
extern void MIi_CpuClear32(u32 data, void *dest, u32 size);
extern int Utf8ToUcs2Bounded(const char *src, u16 *dst, int dstCount);
extern BOOL GetPanelCursorOverride(s32 *outSelection, ScreenPoint *outPosition);
extern void GetActorBalloonAnchor(ScreenPoint *outPoint, int actorId);
extern int GetScreenQuadrantFlags(ScreenPoint *point);
extern void AccumulateTextBoxScroll(ScriptContext *context, ScriptOperand *textOperand, int windowId, s32 selection, ScreenPoint *position);
extern BOOL OpenTextWindowWithText(int windowId, s32 selection, ScreenPoint *position, int style, const u16 *text);

int ScriptCmd_OpenActorTextWindow(ScriptContext *context, ScriptOperand *operands)
{
    ScriptOperand *op = operands;
    ScriptOperand *textOperand;
    int actorId;
    const char *utf8;
    int windowId;
    ScreenPoint position;
    s32 selection;
    int style;
    u16 text[0x100];

    actorId = ScriptVm_ReadOperandInt(context, op++);
    textOperand = op;
    utf8 = ByteCode_ResolveOperand(context, op++);
    windowId = ScriptVm_ReadOperandInt(context, op++);
    selection = ScriptVm_ReadOperandInt(context, op++);
    style = ScriptVm_ReadOperandInt(context, op++);
    if (context->isSkipping != 0) {
        return 1;
    }
    GetActorBalloonAnchor(&position, actorId);
    if (selection == -1) {
        selection = GetScreenQuadrantFlags(&position);
    }
    MIi_CpuClear32(0, text, sizeof(text));
    Utf8ToUcs2Bounded(utf8, text, 0x100);
    if (!GetPanelCursorOverride(&selection, &position)) {
        AccumulateTextBoxScroll(context, textOperand, windowId, selection, &position);
    }
    OpenTextWindowWithText(windowId, selection, &position, style, text);
    return 1;
}
