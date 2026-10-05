#include "nitro/types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x930];
    u8 playerIndex;
    u8 pad_0931[0x944 - 0x931];
    int state;
    u8 pad_0948[0x1808 - 0x948];
    ActorStateFunc setState;
};

extern void *func_ov001_0206db78(u8 index);
extern s32 func_ov059_020c98a0(Actor *actor);
extern BOOL func_ov021_020a753c(void *holder, u16 mask);
extern BOOL func_ov021_020a7524(void *target);
extern BOOL func_ov059_020cb930(Actor *actor);
extern BOOL Actor_AnyAnimSlotBit0Set(Actor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void Actor_UpdateChargeCommand(Actor *actor, void *input);

int Actor_SelectInputState(Actor *actor) {
    void *input = func_ov001_0206db78(actor->playerIndex);

    if (func_ov059_020c98a0(actor) == 0) {
        if (func_ov021_020a753c(input, 2)) {
            actor->setState(actor, 2);
            if (actor->state == 2) {
                return 2;
            }
        }
        if (func_ov021_020a753c(input, 0x800)) {
            if (func_ov021_020a7524(input) && func_ov059_020cb930(actor)) {
                actor->setState(actor, 5);
                if (actor->state == 5) {
                    return 5;
                }
            } else if (Actor_AnyAnimSlotBit0Set(actor) && !func_ov001_020645c8(0x3520)
                       && IsPlayerEntryFlagSet(actor->playerIndex, 11)) {
                actor->setState(actor, 6);
                if (actor->state == 6) {
                    return 6;
                }
            }
        }
        Actor_UpdateChargeCommand(actor, input);
    }
    return actor->state;
}
