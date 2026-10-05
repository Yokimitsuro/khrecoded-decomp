#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Player {
    u8 pad_000[0x128];
    u8 statusFlags;
    u8 pad_129[0x143];
    u32 stateMask : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x18];
    u16 unk_288_0 : 2;
    u16 mode : 2;
    u16 unk_288_4 : 9;
    u16 locked : 1;
    u16 unk_288_14 : 2;
} Player;

typedef struct TargetObject {
    u8 pad_00[0xd];
    u8 armed;
    u8 pad_0e[0x5e];
    int type;
} TargetObject;

typedef struct TargetRef {
    TargetObject *object;
    int kind;
} TargetRef;

typedef struct HitPoints {
    VecFx32 start;
    VecFx32 end;
} HitPoints;

typedef struct AttackQuery {
    Player *player;
    BOOL hit;
    BOOL blocked;
    HitPoints points;
} AttackQuery;

BOOL FilterPlayerAttackTarget(TargetRef *target, HitPoints *points, AttackQuery *query)
{
    Player *player = query->player;

    if (player->mode == 1 || player->locked || (player->stateMask & 0x80)) {
        TargetObject *object = target->object;
        if (object != NULL && target->kind == 4) {
            int type = object->type;
            if (type == 0x1e && object->armed != 0) {
                query->blocked = TRUE;
            } else if (type == 0xc) {
                query->blocked = TRUE;
            } else if ((u32)(type - 1) <= 1) {
                if (query != NULL) {
                    if (player != NULL && (player->statusFlags & 2)) {
                        return FALSE;
                    }
                    if (points != NULL) {
                        query->points = *points;
                    }
                    query->hit = TRUE;
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}
