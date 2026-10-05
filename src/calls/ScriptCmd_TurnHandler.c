#include "nitro/types.h"

extern void ApplyRecordTableEntry4(u16 value);
extern int IsRecordIdFree(int id);
extern void ApplyRecordTableEntry(u16 value, int obj, int a, int b);
extern void ScriptCmd_SetElemField(int scriptCtx, int value);

int ScriptCmd_TurnHandler(int scriptCtx, int angle)
{
    if (angle < 0) {
        if (angle == -0x63) {
            angle = 0;
        }
        ApplyRecordTableEntry4(-angle & 0xffff);
        *(int *)(*(int *)(scriptCtx + 0x1c8) + 8) = 0;
        return 1;
    }
    if (IsRecordIdFree(*(int *)(*(int *)(*(int *)(scriptCtx + 0x1c8) + 8) + 0xc)) != 0) {
        ApplyRecordTableEntry(angle & 0xffff, *(int *)(*(int *)(scriptCtx + 0x1c8) + 8), 0, 0xd);
        if (angle == 0) {
            ScriptCmd_SetElemField(scriptCtx, -0x63);
        } else {
            ScriptCmd_SetElemField(scriptCtx, -angle);
        }
    }
    return 0;
}
