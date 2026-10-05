#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u16 flagsLow : 2;
    u16 moving : 1;
    u16 flag3 : 1;
    u16 attacking : 1;
    u16 flags5 : 2;
    u16 damaged : 1;
    u16 flag8 : 1;
    u16 dying : 1;
    u16 flagsHigh : 6;
} ScriptObject;

BOOL IsObjectIdle(ScriptObject *object) {
    BOOL idle = TRUE;

    if (object->moving || object->attacking || object->damaged || object->dying) {
        idle = FALSE;
    }
    return idle;
}
