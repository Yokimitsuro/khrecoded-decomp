#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_000[0x50];
    int speakerId;
    u8 pad_054[0x74];
    char pendingText[0x108];
    BOOL hasPendingText;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x45c];
    BOOL skipMessages;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern BOOL IsFieldPanelShown(void);
extern u32 func_ov001_0207a648(int speakerId);
extern BOOL SplitTextAtLineBreak(char *text, char *dest);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void ShowMessageWindowMode1(int speakerId, int mode, u16 *text, int flags);

int ScriptCmd_ShowSpeakerMessage(ScriptContext *context, ScriptOperand *operands)
{
    int speakerId = ScriptVm_ReadOperandInt(context, &operands[0]);
    char *text;
    u16 wideText[256];

    ScriptVm_ReadOperandInt(context, &operands[1]);
    text = ByteCode_ResolveOperand(context, &operands[2]);
    if (context->skipMessages) {
        return 1;
    }
    if (!IsFieldPanelShown()) {
        return 0;
    }
    context->scene->speakerId = speakerId;
    if (func_ov001_0207a648(speakerId) == 0) {
        if (SplitTextAtLineBreak(text, context->scene->pendingText)) {
            context->scene->hasPendingText = TRUE;
        }
        Utf8ToUcs2(text, wideText, 256);
        ShowMessageWindowMode1(context->scene->speakerId, 1, wideText, 0);
    }
    return 1;
}
