#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionQuery {
    VecFx32 *origin;
    VecFx32 *delta;
    int mask;
    u16 unk_0c;
    u16 layerMask;
    void *filter;
    u8 pad_14[0x4c];
} CollisionQuery;

typedef struct CollisionHit {
    u8 pad_00[0x2c];
    fx32 fraction;
} CollisionHit;

typedef struct LinkItem {
    u8 pad_00[0xc];
    fx32 height;
} LinkItem;

typedef struct LinkInfo {
    u32 pad_00;
    u32 count;
    u8 pad_08[4];
    LinkItem *items[1];
} LinkInfo;

typedef struct LinkData {
    u8 pad_00[8];
    LinkInfo *info;
} LinkData;

typedef struct StageLink {
    u16 id;
    u8 pad_02[2];
    LinkData *data;
} StageLink;

typedef struct StageObject {
    u8 pad_00[0xe];
    u16 linkId;
    u8 pad_10[0x51];
    u8 linked;
} StageObject;

extern const VecFx32 data_0205344c;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern CollisionHit *ResetAndQueryWorldCollision(CollisionQuery *query);
extern void AddScaledVector(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern StageLink *FindStageLink(u32 id);

static inline s32 GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline u32 GetLinkItemCount(StageLink *link)
{
    if (link == NULL) {
        return 0;
    }
    if (link->data == NULL) {
        return 0;
    }
    return link->data->info->count;
}

static inline LinkItem *GetLinkItem(StageLink *link, u32 index)
{
    LinkItem *item;
    u32 count;

    if (link == NULL) {
        return NULL;
    }
    if (link->data == NULL) {
        return NULL;
    }
    count = GetLinkItemCount(link);
    item = link->data->info->items[index];
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return item;
}

void SnapToStageGround(StageObject *object, VecFx32 *from, fx32 lift, VecFx32 *pos, int mask, VecFx32 *out)
{
    CollisionQuery query;
    VecFx32 start;
    VecFx32 target;
    VecFx32 hitPos;
    VecFx32 origin;
    VecFx32 dir;
    CollisionHit *hit;
    fx32 groundY;
    StageLink *link;
    LinkItem *item;

    groundY = 0;
    query.mask = mask;
    query.layerMask = 0x30;
    query.unk_0c = 0;
    query.filter = NULL;
    *out = *pos;
    start = *from;
    target = *pos;
    VEC_Subtract(&target, &start, &dir);
    dir.y = 0;
    origin = *pos;
    if (GetSessionMode() == 6) {
        origin.y += lift;
    } else {
        origin.y += 0x5000;
    }
    dir = data_0205344c;
    dir.y -= 0xa000;
    query.origin = &origin;
    query.delta = &dir;
    hit = ResetAndQueryWorldCollision(&query);
    if (hit != NULL) {
        AddScaledVector(hit->fraction, query.delta, query.origin, &hitPos);
        groundY = hitPos.y;
    }
    if (groundY > target.y) {
        out->y = groundY;
    }
    if (object->linked) {
        link = FindStageLink(object->linkId);
        if (link != NULL) {
            item = GetLinkItem(link, 0);
            if (item != NULL && item->height != 0 && out->y - groundY < item->height) {
                out->y = groundY + item->height;
            }
        }
    }
}
