#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa8];
    VecFx32 position;
} ActorNode;

typedef struct {
    u8 pad_000[0x50];
    int balloonStyle;
    u8 pad_054[0xc8 - 0x54];
    char savedText[0x104];
    BOOL pendingText;
    int pendingPage;
} BalloonState;

typedef struct {
    u8 pad_000[0x1c8];
    BalloonState *balloon;
} ScriptContext;

typedef struct {
    s16 kind;
    u8 pad_02[6];
} ScriptOperand;

typedef struct {
    int count;
    BOOL isPair;
    u16 **choices;
    int selected;
} ChoiceOptions;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern char *strcpy(char *dst, const char *src);
extern BOOL SplitTextAtLineBreak(char *text, char *dest);
extern void Utf8ToUcs2(const char *src, u16 *dst, u32 length);
extern void OpenActorSpeechBalloon(ScriptContext *context, void *message, int actorId);
extern int func_ov001_02088b48(int actorId);
extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern int CountFlaggedGroupEntries(int group);
extern int CountGroupFlaggedEntries(int group);
extern u16 *FormatWideText(const u16 *format, u16 *dest, u32 destLength, ...);
extern BOOL ActorSlot_GetByIndex(u16 actorId);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void OpenType8BalloonAtPosition(int style, const VecFx32 *worldPos, void *message, void *options);

BOOL OpenScriptChoiceBalloon(ScriptContext *context, ScriptOperand *operand)
{
    char *text;
    int actorId;
    int i;
    int count;
    u16 splitText[0x100];
    u16 message[0x100];
    u16 formatted[0x100];
    u16 choiceText[6][0x40];
    char *args[6];
    ChoiceOptions options;
    u16 *choicePtrs[6];
    VecFx32 position;
    int group;
    int flagged;
    int total;
    int available;
    ScriptOperand *textOperand;

    actorId = ScriptVm_ReadOperandInt(context, operand);
    textOperand = operand + 1;
    operand += 2;
    text = ByteCode_ResolveOperand(context, textOperand);
    if (context->balloon->pendingText) {
        context->balloon->pendingText = FALSE;
        strcpy(text, context->balloon->savedText);
    }
    if (!context->balloon->pendingText && SplitTextAtLineBreak(text, context->balloon->savedText)) {
        Utf8ToUcs2(text, splitText, 0x100);
        OpenActorSpeechBalloon(context, splitText, actorId);
        context->balloon->pendingText = TRUE;
        context->balloon->pendingPage = 0;
        return FALSE;
    }
    for (count = 0; count < 6; count++) {
        if (operand->kind == 0) {
            break;
        }
        args[count] = ByteCode_ResolveOperand(context, operand);
        operand++;
    }
    context->balloon->balloonStyle = func_ov001_02088b48(actorId);
    options.count = count;
    options.isPair = count == 2;
    options.selected = 0;
    for (i = 0; i < count; i++) {
        choicePtrs[i] = choiceText[i];
        Utf8ToUcs2(args[i], choicePtrs[i], 0x200);
    }
    options.choices = choicePtrs;
    if (context->balloon->pendingText) {
        Utf8ToUcs2(context->balloon->savedText, message, 0x100);
        MIi_CpuClear32(0, context->balloon->savedText, 0x100);
        context->balloon->pendingText = FALSE;
    } else {
        Utf8ToUcs2(text, message, 0x100);
    }
    if (actorId == -1) {
        OpenType8BalloonAtPosition(context->balloon->balloonStyle, NULL, message, &options);
    } else if (actorId == -2) {
        group = ReadSessionPackedBits(0x362b, 5);
        flagged = CountFlaggedGroupEntries(group);
        available = CountGroupFlaggedEntries(group);
        total = 0;
        switch (group) {
        case 2:
            total = 20;
            break;
        case 3:
            total = 30;
            break;
        case 8:
            total = 20;
            break;
        case 9:
            total = 60;
            break;
        case 13:
            total = 20;
            break;
        case 14:
            total = 40;
            break;
        case 18:
            total = 50;
            break;
        case 19:
            total = 70;
            break;
        case 21:
            total = 80;
            break;
        }
        if (total == 0) {
            FormatWideText(message, formatted, 0x100, flagged, available);
        } else {
            FormatWideText(message, formatted, 0x100, flagged, available, total);
        }
        OpenType8BalloonAtPosition(context->balloon->balloonStyle, NULL, formatted, &options);
    } else if (ActorSlot_GetByIndex(actorId)) {
        position = ActorRegistry_GetEntityByIndex(actorId)->position;
        OpenType8BalloonAtPosition(context->balloon->balloonStyle, &position, message, &options);
    } else {
        OpenType8BalloonAtPosition(context->balloon->balloonStyle, NULL, message, &options);
    }
    return TRUE;
}
