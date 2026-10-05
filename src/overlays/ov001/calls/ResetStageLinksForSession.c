#include "nitro/types.h"

typedef struct ActorLink {
    u8 pad_00[0x10];
    u16 active;
} ActorLink;

typedef struct StageManager {
    u32 flags;
    u8 pad_004[0x18d7c - 4];
    void *linkList;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern ActorLink *func_ov001_0208f290(void *list, void *node);
extern void *func_ov001_0208f2a4(void *list);
extern void *func_ov001_0208f2b4(void *node);
extern void ResetLinkedActorMotion(ActorLink *link);

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

void ResetStageLinksForSession(void)
{
    BOOL reset;
    void *node;
    ActorLink *link;

    if (data_ov001_020a0528 == NULL) {
        return;
    }
    reset = FALSE;
    if (func_ov001_02063a24() && func_ov001_020645c8(0x3628)) {
        reset = TRUE;
    } else if (GetSessionMode() == 10 && !func_ov001_020645c8(0x380c)) {
        reset = TRUE;
    } else if (GetSessionMode() == 6 && !func_ov001_020645c8(0x379e)) {
        reset = TRUE;
    }
    if (reset) {
        data_ov001_020a0528->flags |= 0x40;
        node = func_ov001_0208f2a4(data_ov001_020a0528->linkList);
        if (node == NULL) {
            return;
        }
        do {
            link = func_ov001_0208f290(data_ov001_020a0528->linkList, node);
            node = func_ov001_0208f2b4(node);
            if (link->active != 0) {
                ResetLinkedActorMotion(link);
            }
        } while (node != NULL);
        return;
    }
    data_ov001_020a0528->flags |= 2;
}
