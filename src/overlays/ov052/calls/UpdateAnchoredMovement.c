#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 kind;
    u8 group;
    u8 id;
} CarryTarget;

typedef struct {
    u8 pad_000[0x194];
    CarryTarget target;
} CarryInfo;

typedef struct {
    u8 pad_00[0x30];
    BOOL (*isBusy)(void *object);
} CarryObjectVtbl;

typedef struct {
    u8 pad_00[4];
    CarryObjectVtbl *vtbl;
} CarryObject;

typedef struct {
    u8 pad_00[0xc];
    u8 flags;
    u8 pad_0d[0x14 - 0x0d];
    CarryInfo *info;
    u8 pad_18[0x6c - 0x18];
    int state;
} CarryLink;

typedef struct {
    VecFx32 position;
    u8 pad_0c[0x1c - 0x0c];
    CarryLink *link;
} CarryAnchor;

typedef struct CarryActor CarryActor;

struct CarryActor {
    u8 pad_000[0x1f8];
    void (*notify)(CarryActor *actor, int event, int arg);
    u8 pad_1fc[0x75c - 0x1fc];
    int linkMode;
    u8 pad_760[0x768 - 0x760];
    int linked;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0x9c4 - 0x9b5];
    int speed;
    u8 pad_9c8[0xa54 - 0x9c8];
    CarryAnchor anchor;
    u8 pad_a74[0x10ec - 0xa74];
    void (*changeMode)(CarryActor *actor, int mode);
    u8 pad_10f0[0x10fc - 0x10f0];
    BOOL (*idle)(CarryActor *actor);
};

extern u32 func_ov001_0207f060(u32 group, u32 id);
extern int ForwardIfWorkMode12(u32 task, VecFx32 *out, CarryTarget *target);
extern CarryObject *func_ov001_0208724c(u32 group, u32 id);
extern int Object_GetKindValue(CarryObject *object);
extern BOOL IsFieldUnitAction5Mode1(CarryObject *unit);
extern BOOL func_ov001_020863f4(CarryObject *object, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov052_020ceb80(CarryActor *actor, VecFx32 *position);
extern BOOL func_ov052_020c9294(CarryActor *actor, VecFx32 *position);
extern void *func_ov001_0206db78(int player);
extern BOOL func_ov021_020a7524(void *self);
extern u16 func_ov021_020a7564(void *self);
extern u16 GetLinkedAngleOffset(CarryActor *actor);
extern s32 func_ov001_02063a38(void);
extern BOOL HasFlagsAt0xe(void *holder, u16 mask);
extern BOOL HasFlagsAt0xc(void *holder, u16 mask);
extern void EnterRecoilState(CarryActor *actor);

void UpdateAnchoredMovement(CarryActor *actor)
{
    CarryAnchor *anchor = &actor->anchor;
    BOOL recoil = FALSE;
    BOOL attached = FALSE;
    CarryLink *link;
    VecFx32 offset;

    if (actor->linked != 0 && actor->linkMode == 3 && actor->notify != NULL) {
        actor->notify(actor, 4, -1);
    }
    link = anchor->link;
    if (link != NULL) {
        if (link->info != NULL) {
            attached = TRUE;
        } else {
            recoil = TRUE;
        }
    }
    if (attached) {
        BOOL moved = FALSE;
        CarryTarget *info = &link->info->target;
        CarryObject *object;
        BOOL busy;

        switch (info->kind) {
        case 1:
            if (link->state != 0x1a) {
                recoil = TRUE;
            } else if (link->flags & 2) {
                recoil = TRUE;
            }
            break;
        case 2:
            if (ForwardIfWorkMode12(func_ov001_0207f060(info->group, info->id), &offset, info)) {
                moved = TRUE;
            }
            break;
        case 4:
            object = func_ov001_0208724c(info->group, info->id);
            if (object->vtbl->isBusy != NULL) {
                busy = object->vtbl->isBusy(object);
            } else {
                busy = FALSE;
            }
            if (busy) {
                recoil = TRUE;
                break;
            }
            if (Object_GetKindValue(object) == 5 && IsFieldUnitAction5Mode1(object)) {
                recoil = TRUE;
            }
            if (!recoil && func_ov001_020863f4(object, &offset)) {
                moved = TRUE;
            }
            break;
        }
        if (moved) {
            VEC_Add(&offset, &anchor->position, &anchor->position);
        }
    }
    func_ov052_020ceb80(actor, &anchor->position);
    actor->stateFlags |= 1;
    if (!(actor->stateFlags & 0x80000000) && (actor->stateFlags & 0x20)) {
        recoil = TRUE;
    }
    if (!func_ov052_020c9294(actor, &anchor->position)) {
        recoil = TRUE;
    }
    if (!recoil) {
        void *source = func_ov001_0206db78(actor->player);
        BOOL facingSide = FALSE;
        BOOL turn = FALSE;

        if (actor->speed >= 0x6000) {
            if (func_ov021_020a7524(source)) {
                u16 sourceAngle = func_ov021_020a7564(source);
                int diff = (u16)(GetLinkedAngleOffset(actor) - sourceAngle);
                if (diff <= 0x2aaa || diff >= 0xd555) {
                    turn = TRUE;
                } else if (diff >= 0x71c8 && diff <= 0x8e38) {
                    facingSide = TRUE;
                }
            }
            if (func_ov001_02063a38() == 4 && HasFlagsAt0xe(source, 0x40)) {
                turn = TRUE;
            }
        }
        if (turn) {
            actor->changeMode(actor, 7);
            return;
        }
        if (HasFlagsAt0xc(source, 2) || facingSide) {
            recoil = TRUE;
        }
    }
    if (recoil) {
        EnterRecoilState(actor);
        return;
    }
    if (!actor->idle(actor)) {
        return;
    }
}
