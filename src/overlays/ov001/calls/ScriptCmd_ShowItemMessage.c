#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    int skipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern void PlaySoundChecked(void *ptr, int arg);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern BOOL IsFieldPanelShown(void);
extern void ShowMessageWindowMode3(u16 *text);
extern u32 GetFieldHandle(s32 handleIndex);
extern u16 *FormatWideText(const u16 *format, u16 *dest, u32 destLength, ...);
extern void GrantRecordItem(int itemId);
extern void OpenActorSpeechBalloon(ScriptContext *context, u16 *text, int speaker);

int ScriptCmd_ShowItemMessage(ScriptContext *context, ScriptOperand *operands)
{
    u16 format[0x100];
    u16 formatted[0x100];
    int speaker = ScriptVm_ReadOperandInt(context, operands);
    int kind = ScriptVm_ReadOperandInt(context, operands + 1);
    char *text = ByteCode_ResolveOperand(context, operands + 2);
    int itemId = ScriptVm_ReadOperandInt(context, operands + 3);

    if (context->skipping != 0) {
        if (kind == 1) {
            GrantRecordItem(itemId);
        }
        return 1;
    }
    if (!IsFieldPanelShown()) {
        return 0;
    }
    Utf8ToUcs2(text, format, 0x100);
    switch (kind) {
    case 0:
        FormatWideText(format, formatted, 0x100, itemId);
        OpenActorSpeechBalloon(context, formatted, speaker);
        break;
    case 1:
        FormatWideText(format, formatted, 0x100, GetFieldHandle(itemId));
        ShowMessageWindowMode3(formatted);
        GrantRecordItem(itemId);
        PlaySoundChecked(0, 9);
        break;
    case 2:
        break;
    }
    return 1;
}
