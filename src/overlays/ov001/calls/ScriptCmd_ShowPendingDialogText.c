#include "nitro/types.h"

typedef struct ScriptSceneData {
    u8 pad_000[0x50];
    void *balloon;
    u32 speakerId;
    u8 pad_058[0xc8 - 0x58];
    char pendingText[0x100];
    u8 pad_1c8[4];
    BOOL unk_1CC;
    BOOL balloonActive;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern u32 func_ov001_0207a648(void *operands);
extern u32 func_ov001_0207a810(void);
extern char *strcpy(char *dst, const char *src);
extern BOOL SplitTextAtLineBreak(char *text, char *dest);
extern int Utf8ToUcs2(const char *src, u16 *dst, int maxChars);
extern void ShowMessageWindowMode1(void *balloon, int mode, u16 *text, int flags);
extern void OpenActorSpeechBalloon(ScriptContext *context, u16 *text, u32 speakerId);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

int ScriptCmd_ShowPendingDialogText(ScriptContext *context, void *operands)
{
    ScriptSceneData *scene;
    char lineText[0x100];
    u16 wideText[0x100];

    if (func_ov001_0207a648(operands) == 0) {
        scene = context->scene;
        if (scene->unk_1CC == 0 && scene->pendingText[0] != 0) {
            strcpy(lineText, scene->pendingText);
            SplitTextAtLineBreak(lineText, context->scene->pendingText);
            Utf8ToUcs2(lineText, wideText, 0x100);
            scene = context->scene;
            if (scene->balloonActive != 0) {
                ShowMessageWindowMode1(scene->balloon, 1, wideText, 0);
            } else {
                OpenActorSpeechBalloon(context, wideText, scene->speakerId);
            }
            return 0;
        }
        WriteSessionPackedBits(0x3521, 4, func_ov001_0207a810());
        return 1;
    }
    return 0;
}
