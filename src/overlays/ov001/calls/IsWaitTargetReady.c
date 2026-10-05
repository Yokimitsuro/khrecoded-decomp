#include "nitro/types.h"

typedef struct WaitSubject {
    u8 pad_00[0xbc];
    u8 readyState[4];
} WaitSubject;

typedef struct WaitTarget {
    u8 kind;
    u8 pad_01[3];
    union {
        u16 eventId;
        int entry;
        WaitSubject *subject;
    } u;
} WaitTarget;

extern int IsStageEventReady(u32 id);
extern u32 func_ov001_0207f898(int entry);
extern u32 func_ov001_0208641c(int entry);

BOOL IsWaitTargetReady(WaitTarget *target)
{
    BOOL ready = FALSE;

    switch (target->kind) {
    case 2:
        if (func_ov001_0207f898(target->u.entry) != 0) {
            ready = TRUE;
        }
        break;
    case 3:
        if (func_ov001_0208641c(target->u.entry) != 0) {
            ready = TRUE;
        }
        break;
    case 1:
        if (IsStageEventReady(target->u.eventId) != 0) {
            ready = TRUE;
        }
        break;
    case 4:
        if (target->u.subject->readyState != NULL) {
            ready = TRUE;
        }
        break;
    }
    return ready;
}
