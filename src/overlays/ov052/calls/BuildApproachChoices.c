#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CrowdNode {
    struct CrowdNode *next;
} CrowdNode;

typedef struct {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x24 - 0x14];
} EventTargetInfo;

typedef struct ChoiceActor ChoiceActor;

struct ChoiceActor {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x22c - 0x1e0];
    int (*getState)(ChoiceActor *actor);
    u8 pad_230[0x1048 - 0x230];
    u8 waitTarget[4];
};

extern VecFx32 *GetWaitTargetPosition(void *target);
extern VecFx32 *func_ov052_020ceb74(ChoiceActor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern CrowdNode *func_ov001_02087264(void);
extern VecFx32 *func_ov001_0208641c(CrowdNode *node);
extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 id);
extern int IsStageEventReady(u32 id);
extern BOOL func_ov001_02087988(u32 id, EventTargetInfo *out);

void BuildApproachChoices(ChoiceActor *actor, BOOL above, int *choices)
{
    fx32 distance;
    BOOL crowded = FALSE;
    int count = 0;
    VecFx32 *target = GetWaitTargetPosition(actor->waitTarget);
    VecFx32 *self = func_ov052_020ceb74(actor);
    VecFx32 diff;
    EventTargetInfo info;
    fx32 height;
    int i;
    int state;
    BOOL near;

    VEC_Subtract(target, self, &diff);
    diff.y = 0;
    distance = VEC_Mag(&diff);
    for (i = 0; i < 6; i++) {
        choices[i] = -1;
    }
    if (distance < 0x6000) {
        if (!above) {
            if (target->y - self->y > 0x2000) {
                if (actor->getState != NULL) {
                    state = actor->getState(actor);
                } else {
                    state = actor->state;
                }
                if (state != 6) {
                    choices[0] = 4;
                    return;
                }
            }
        } else if (self->y - target->y > 0x2000) {
            choices[0] = 5;
            count++;
        }
    }
    near = FALSE;
    height = target->y - self->y;
    if (height < 0) {
        height = -height;
    }
    if (VEC_Distance(self, target) < 0x3000 && height < 0x1800) {
        near = TRUE;
    }
    if (near) {
        int nearby = 0;
        CrowdNode *node;
        s32 event;

        for (node = func_ov001_02087264(); node != NULL; node = node->next) {
            VecFx32 *position = func_ov001_0208641c(node);
            if (position != NULL) {
                height = position->y - self->y;
                if (height < 0) {
                    height = -height;
                }
                if (VEC_Distance(self, position) < 0x3000 && height < 0x1800) {
                    nearby++;
                }
            }
        }
        for (event = ForwardToActiveServiceWithResult(); event != 0; event = func_ov001_0208796c(event)) {
            if (IsStageEventReady(event) && func_ov001_02087988(event, &info)) {
                height = info.position.y - self->y;
                if (height < 0) {
                    height = -height;
                }
                if (VEC_Distance(self, &info.position) < 0x3000 && height < 0x1800) {
                    nearby++;
                }
            }
        }
        if (nearby >= 2) {
            choices[count] = 3;
            count++;
            crowded = TRUE;
        }
    }
    if (distance <= 0x2000) {
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
        choices[count] = 1;
        count++;
        choices[count] = 2;
        count++;
    } else if (distance > 0x2000 && distance < 0x5000) {
        choices[count] = 1;
        count++;
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
        choices[count] = 2;
        count++;
    } else if (distance >= 0x5000) {
        choices[count] = 2;
        count++;
        choices[count] = 1;
        count++;
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
    }
}
