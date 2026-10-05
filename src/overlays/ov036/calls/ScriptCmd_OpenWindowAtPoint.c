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
extern void GetActorBalloonAnchor(ScreenPoint *out, int actorId);
extern int GetScreenQuadrantFlags(ScreenPoint *point);
extern void OpenTextWindow(int balloonId, int direction, ScreenPoint *point, int style);

int ScriptCmd_OpenWindowAtPoint(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt(context, &operands[0]);
    int balloonId = ScriptVm_ReadOperandInt(context, &operands[1]);
    int direction = ScriptVm_ReadOperandInt(context, &operands[2]);
    int style = ScriptVm_ReadOperandInt(context, &operands[3]);
    ScreenPoint point;

    if (context->isSkipping != 0) {
        return 1;
    }
    if (operands[4].type == 0) {
        GetActorBalloonAnchor(&point, actorId);
        if (direction == -1) {
            direction = GetScreenQuadrantFlags(&point);
        }
        point.x = 0x80;
        point.y = 0x60;
    } else {
        point.x = ScriptVm_ReadOperandInt(context, &operands[4]);
        point.y = ScriptVm_ReadOperandInt(context, &operands[5]);
        if (direction == -1) {
            direction = GetScreenQuadrantFlags(&point);
        }
    }
    OpenTextWindow(balloonId, direction, &point, style);
    return 1;
}
