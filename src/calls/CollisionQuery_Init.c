#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct QueryWorkspace {
    u8 pad_000[0x180];
    u8 unk_180;
    u8 pad_181[0x20];
    u8 unk_1A1;
} QueryWorkspace;

typedef struct CollisionQuery {
    u8 pad_00[0x0e];
    u16 id;
    void *actor;
    s32 unk_14;
    u8 pad_18[0x0c];
    void *shape;
    QueryWorkspace *workspace;
    fx32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 unk_3C;
    u8 unk_3D;
    u8 unk_3E;
    u8 pad_3F;
    u8 kind;
    u8 pad_41[3];
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[4];
    s32 unk_50;
    u8 pad_54[4];
    s32 unk_58;
} CollisionQuery;

void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, s32 unk44)
{
    query->id = id;
    query->actor = actor;
    query->kind = kind;
    query->unk_3C = unk3C;
    query->unk_3D = unk3D;
    query->unk_3E = 1;
    query->unk_2C = 0x3000;
    query->shape = shape;
    query->workspace = workspace;
    query->unk_44 = unk44;
    query->unk_14 = 0;
    query->unk_30 = -1;
    query->unk_34 = -1;
    query->unk_38 = -1;
    query->unk_48 = 0;
    query->unk_50 = 0;
    query->unk_58 = 0;
    workspace->unk_180 = 0;
    workspace->unk_1A1 = 0;
}
