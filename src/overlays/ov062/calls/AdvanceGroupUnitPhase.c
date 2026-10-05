#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[8];
    int soundId;
} SoundHandle;

typedef struct UnitObj {
    u8 pad_00[2];
    s8 state;
    u8 pad_03[0x2f];
    s16 phase;
    u8 pad_34[0x11c];
    SoundHandle *sound;
} UnitObj;

typedef struct {
    u8 pad_00[8];
    UnitObj *leader;
} UnitGroup;

extern int func_ov021_020ab43c(UnitObj *owner, fx32 step);
extern void func_ov021_020ab310(UnitObj *rig, int blend);
extern void func_ov021_020ab610(UnitObj *obj);
extern void PlaySoundChecked(int id, int flag);
extern void func_ov021_020af564(int a, int b);

BOOL AdvanceGroupUnitPhase(UnitGroup *group, UnitObj *unit, fx32 step)
{
    UnitObj *leader = group->leader;
    SoundHandle *sound = unit->sound;
    s16 phase = unit->phase;
    int done = func_ov021_020ab43c(unit, step);

    switch (phase) {
    case 0:
        if (unit == leader) {
            if (done != 0) {
                func_ov021_020ab310(unit, 1);
            }
        } else if (leader->phase != 0) {
            func_ov021_020ab310(unit, 1);
        }
        break;
    case 1:
        if (done != 0) {
            func_ov021_020ab610(unit);
        }
        if (unit == leader) {
            PlaySoundChecked(sound->soundId, 1);
            func_ov021_020af564(3, 0);
        }
        break;
    }
    if (unit->state == -1) {
        return TRUE;
    }
    return FALSE;
}
