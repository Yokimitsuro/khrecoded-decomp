#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Entity;

typedef struct EntityDef {
    u8 pad_00[0x30];
    BOOL (*isBusy)(struct Entity *entity);
    u8 pad_34[0xa];
    u16 childCount;
} EntityDef;

typedef struct Entity {
    u8 pad_00[4];
    EntityDef *def;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0xc];
    s32 kind : 16;
    s32 mode : 12;
    s32 : 4;
    u8 pad_54[0xc];
    u8 *script;
    u8 pad_64[4];
    s32 timer;
    s16 target;
} Entity;

typedef struct PoolNode {
    struct PoolNode *next;
    u32 slot : 8;
    s32 action : 8;
    u32 : 9;
    u32 pending : 1;
    u32 : 6;
    union {
        VecFx32 position;
        s32 handle;
    } data;
} PoolNode;

typedef struct {
    VecFx32 offset;
    u8 flagA;
    u8 flagB;
    s32 limit;
    s32 unk_14;
    s32 unk_18;
} MoveParams;

typedef struct {
    u8 pad_00[0x14];
    s32 mode;
} Request;

typedef struct {
    u8 pad_00[4];
    s32 state;
} Context;

extern const VecFx32 data_0205344c;

extern PoolNode **GetPool4Entry(Entity *owner, int index);
extern BOOL func_ov042_020bd7ac(void);
extern Entity *func_ov001_02086384(EntityDef *def, int index);
extern BOOL IsFieldIdle(Entity *entity);
extern BOOL FindSlotLinkedObject(PoolNode **pool, Entity *entity);
extern void func_ov001_02086408(Entity *entity, MoveParams *params);
extern void func_ov017_020a3d94(Entity *entity, BOOL enable);
extern BOOL IsFieldFlagBit1Set(Entity *entity);
extern BOOL IsState2(Entity *entity);
extern void ResetFieldObjectToIdle(Entity *entity);
extern void func_ov017_020a3c98(Entity *entity, int value);
extern void SetFieldObjectPosition_020a40fc(Entity *entity, VecFx32 *position);
extern void RefreshListHeadAndDispatch(Entity *entity);
extern void func_ov042_020bd600(s32 handle);
extern void StartCameraParticle(VecFx32 *position, int a, int b, int c);
extern void PlaySoundChecked(int id, int mode);

static inline BOOL Entity_IsBusy(Entity *entity)
{
    if (entity->def->isBusy != NULL) {
        return entity->def->isBusy(entity);
    }
    return FALSE;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

int FinishPoolActions(Context *context, Entity *owner, int poolIndex, Request *request)
{
    PoolNode **pool;
    int i;
    Entity *entity;
    PoolNode *node;
    int count;
    MoveParams params;
    MoveParams moveParams;
    VecFx32 effectPos;
    VecFx32 origin;

    pool = GetPool4Entry(owner, poolIndex);
    if (request->mode == 1) {
        return 0;
    }
    if (func_ov042_020bd7ac()) {
        return 1;
    }
    count = owner->def->childCount;
    origin = data_0205344c;
    params.offset = data_0205344c;
    params.flagA = 0;
    params.flagB = 0;
    params.limit = 0x7fffffff;
    params.unk_14 = 0;
    params.unk_18 = 0;
    for (i = 0; i < count; i++) {
        entity = func_ov001_02086384(owner->def, i);
        if (!IsFieldIdle(entity)) {
            continue;
        }
        if (entity->kind != 2) {
            continue;
        }
        if (entity->target == -1 && (entity->script == NULL || *entity->script == 4)) {
            continue;
        }
        if (entity->mode == 0) {
            continue;
        }
        if (entity->mode != 1 && FindSlotLinkedObject(pool, entity)) {
            continue;
        }
        func_ov001_02086408(entity, &params);
    }
    for (node = *pool; node != NULL; node = node->next) {
        if (node->slot != 0xff) {
            entity = func_ov001_02086384(owner->def, node->slot);
        } else {
            entity = NULL;
        }
        switch (node->action) {
        case 0:
            func_ov017_020a3d94(entity, 1);
            if (IsFieldFlagBit1Set(entity) || IsState2(entity)) {
                BOOL inState2 = IsState2(entity);
                if (inState2) {
                    ResetFieldObjectToIdle(entity);
                    entity->timer = 0x1f;
                } else {
                    func_ov017_020a3c98(entity, 0);
                }
                if (inState2 && entity->mode != 2) {
                    SetFieldObjectPosition_020a40fc(entity, &node->data.position);
                    RefreshListHeadAndDispatch(entity);
                } else {
                    node->data.position = entity->position;
                }
                node->pending = 1;
                break;
            }
            if (entity->mode == 2 && FindSlotLinkedObject(pool, entity)) {
                break;
            }
            node->pending = 1;
        case 1:
            if (!Entity_IsBusy(entity)) {
                moveParams.offset = origin;
                moveParams.flagA = 0;
                moveParams.flagB = 0;
                moveParams.limit = 0x7fffffff;
                moveParams.unk_14 = 0;
                moveParams.unk_18 = 0;
                func_ov001_02086408(entity, &moveParams);
            }
            break;
        case 3:
            func_ov042_020bd600(node->data.handle);
            break;
        }
    }
    effectPos = MakeVec(0, 0x4cd, 0);
    StartCameraParticle(&effectPos, 0x666, 0x182, 0x3c000);
    context->state = 0;
    PlaySoundChecked(0x1a4, 2);
    return 1;
}
