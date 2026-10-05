#include "nitro/types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

struct Actor {
    u8 pad_0000[0x930];
    u8 playerIndex;
    u8 pad_0931[0x1808 - 0x931];
    ActorChangeStateFunc changeState;
};

extern void *func_ov001_0206db78(u32 playerIndex);
extern void func_ov059_020c999c(Actor *actor);
extern u16 SharedObject_GetId(void *record);
extern BOOL func_ov021_020a753c(void *record, u16 mask);
extern BOOL func_ov021_020a7524(void *record);
extern BOOL func_ov059_020cb930(Actor *actor);

BOOL Actor_TryEnterState5(Actor *actor)
{
    void *record = func_ov001_0206db78(actor->playerIndex);
    BOOL entered = FALSE;

    func_ov059_020c999c(actor);
    SharedObject_GetId(record);
    if (func_ov021_020a753c(record, 0x800) && func_ov021_020a7524(record) &&
        func_ov059_020cb930(actor)) {
        actor->changeState(actor, 5);
        entered = TRUE;
    }
    return entered;
}
