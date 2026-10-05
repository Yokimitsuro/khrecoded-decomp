#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x54];
    s32 speakerId;
    u8 pad_58[0xc8 - 0x58];
    char pendingLine[0x100];
    u8 pad_1c8[0x1d0 - 0x1c8];
    s32 unk_1D0;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x628 - 0x1cc];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int IsFieldPanelShown(void);
extern BOOL SplitTextAtLineBreak(char *text, char *dest);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void OpenActorSpeechBalloon(ScriptContext *context, u16 *text, int speakerId);

int ScriptCmd_ShowActorMessage(ScriptContext *context, ScriptOperand *operands)
{
    int speakerId;
    char *text;
    u16 wideText[0x200];

    speakerId = ScriptVm_ReadOperandInt(context, operands);
    text = ByteCode_ResolveOperand(context, operands + 1);
    if (context->isSkipping != 0) {
        return 1;
    }
    if (IsFieldPanelShown() == 0) {
        return 0;
    }
    if (SplitTextAtLineBreak(text, context->scene->pendingLine) != 0) {
        context->scene->speakerId = speakerId;
        context->scene->unk_1D0 = 0;
    }
    Utf8ToUcs2(text, wideText, 0x200);
    OpenActorSpeechBalloon(context, wideText, speakerId);
    return 1;
}
