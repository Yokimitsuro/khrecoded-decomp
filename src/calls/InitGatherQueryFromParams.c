#include "nitro/types.h"

typedef struct GatherParams {
    u8 pad_00[0xe];
    u16 groupMask;
    u32 ownerId;
    void *box;
    void *floorList;
    void *wallList;
    void *ceilList;
    s16 limit;
    u8 pad_26[2];
    s16 *floorCount;
    s16 *wallCount;
    s16 *ceilCount;
    u8 pad_34[0xa];
    u8 isStatic;
    u8 pad_3F;
    u8 kindMask;
    u8 pad_41[3];
    s32 unk_44;
    void *filter;
    void *filterUser;
} GatherParams;

typedef struct CollGatherQuery {
    u32 flags;
    u8 pad_04[0x79];
    u8 isStatic;
    u8 pad_7E[0xe];
    u32 ownerId;
    u16 groupMask;
    u8 pad_92;
    u8 kindMask;
    s32 unk_94;
    void *filter;
    void *filterUser;
    void *box;
    void *floorList;
    void *wallList;
    void *ceilList;
    s16 limit;
    u8 pad_B2[2];
    s16 *floorCount;
    s16 *wallCount;
    s16 *ceilCount;
} CollGatherQuery;

void InitGatherQueryFromParams(CollGatherQuery *query, const GatherParams *params)
{
    query->ownerId = params->ownerId;
    query->groupMask = params->groupMask;
    query->isStatic = params->isStatic;
    query->kindMask = params->kindMask;
    query->flags = 0;
    query->unk_94 = params->unk_44;
    query->filter = params->filter;
    query->filterUser = params->filterUser;
    query->box = params->box;
    query->floorList = params->floorList;
    query->wallList = params->wallList;
    query->ceilList = params->ceilList;
    query->limit = params->limit;
    query->floorCount = params->floorCount;
    query->wallCount = params->wallCount;
    query->ceilCount = params->ceilCount;
    *query->floorCount = 0;
    *query->wallCount = 0;
    *query->ceilCount = 0;
}
