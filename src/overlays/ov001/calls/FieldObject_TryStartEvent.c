#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 bit6 : 1;
    u32 unk_7 : 5;
    u32 bit12 : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct Session {
    u8 pad_000[0x20];
    u32 stateFlags;
    u8 pad_024[0x1F0];
    SessionFlags flags;
} Session;

typedef struct FieldObject {
    u8 pad_00[0x58];
    u8 isRunning;
    s8 configFlags;
    u8 pad_5A[0xA];
    char eventLabel[8];
    char scriptName[8];
} FieldObject;

extern Session *data_ov001_020a0480;
extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern BOOL IsFirstEntryFlagSet(void);
extern u32 func_ov001_02063620(void);
extern BOOL func_ov001_02064490(void);
extern BOOL func_ov001_02063694(void);
extern void OpenSessionArchive(char *eventLabel, char *scriptName);
extern void func_ov001_0206e444(BOOL enabled);
extern void SetSessionScriptParams(void (*onFinish)(FieldObject *object), FieldObject *object);
extern void func_ov001_02080e84(FieldObject *object);

BOOL FieldObject_TryStartEvent(FieldObject *object)
{
    if (object->isRunning) {
        return FALSE;
    }
    if (object->scriptName[0] == 0) {
        return FALSE;
    }
    if (!(object->configFlags & 0x80) && FieldObject_GetSavedValue(object) != 0) {
        return FALSE;
    }
    if (IsFirstEntryFlagSet()) {
        return FALSE;
    }
    if (func_ov001_02063620() != 0 || (data_ov001_020a0480->stateFlags & 0x10) ||
        data_ov001_020a0480->flags.bit12 || data_ov001_020a0480->flags.bit6 ||
        func_ov001_02064490()) {
        return FALSE;
    }
    if (func_ov001_02063694()) {
        OpenSessionArchive(object->eventLabel[0] ? object->eventLabel : NULL, object->scriptName);
        func_ov001_0206e444(TRUE);
        SetSessionScriptParams(func_ov001_02080e84, object);
        object->isRunning = TRUE;
    }
    return FALSE;
}
