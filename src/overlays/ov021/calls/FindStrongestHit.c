#include "nitro/types.h"

typedef struct {
    s32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc8];
} HitResult;

typedef struct {
    HitResult result;
    u32 active;
    u32 pad_d8;
} HitScan;

typedef struct {
    u8 data[0x60];
} HitQuery;

typedef struct {
    u8 data[0x28];
} HitFilter;

typedef struct {
    u32 flags;
} UnitType;

typedef struct {
    u8 pad_00[0x138];
    UnitType *type;
} Unit;

typedef struct Attacker Attacker;
typedef void (*HitCallback)(Attacker *attacker, Unit *unit, HitScan *scan);

struct Attacker {
    s32 player;
    u8 pad_04[0x30];
    HitCallback onHit;
    HitCallback onScan;
};

extern void func_ov021_020ac168(HitResult *result);
extern void BuildEntryHitShape(Unit *unit, HitQuery *query, u32 arg0, u32 arg1);
extern s32 GetObjectKindValue(HitQuery *query);
extern void BuildDrawParams(Unit *unit, s32 player, HitFilter *filter);
extern void ZeroAndSetField0xd4(HitScan *scan);
extern BOOL StepHitScan(s32 player, HitQuery *query, HitFilter *filter, HitScan *scan);
extern void AdvanceToSecondPhase(Unit *unit);

HitResult FindStrongestHit(Attacker *attacker, Unit *unit, u32 arg0, u32 arg1)
{
    UnitType *type = unit->type;
    BOOL advance;
    HitQuery query;
    HitScan scan;
    HitResult best;
    HitFilter filter;
    HitScan *cur = &scan;

    func_ov021_020ac168(&best);
    BuildEntryHitShape(unit, &query, arg0, arg1);
    if (GetObjectKindValue(&query) <= 0) {
        return best;
    }
    BuildDrawParams(unit, attacker->player, &filter);
    advance = FALSE;
    ZeroAndSetField0xd4(&scan);
    while (StepHitScan(attacker->player, &query, &filter, &scan)) {
        if (cur->result.strength != 0) {
            if (cur->result.strength == 1) {
                if (!(type->flags & 4)) {
                    advance = TRUE;
                }
                if ((type->flags & 0x2000) && cur->result.side == 2) {
                    advance = FALSE;
                }
            } else if (!(type->flags & 2)) {
                advance = TRUE;
            }
            if (attacker->onScan != NULL) {
                attacker->onScan(attacker, unit, &scan);
            }
            if (cur->result.strength != 0 && best.strength <= cur->result.strength) {
                best = scan.result;
            }
            if (!(type->flags & 0x10) && attacker->onHit != NULL) {
                attacker->onHit(attacker, unit, &scan);
            }
        }
    }
    if (advance) {
        AdvanceToSecondPhase(unit);
    }
    return best;
}
