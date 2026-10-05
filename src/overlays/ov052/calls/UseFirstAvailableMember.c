#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad4[0x3c];
    s16 level;
} Member;

typedef struct {
    Member **members;
} MemberList;

extern int data_ov052_020d20e0[];
extern int FindMemberIndexById(MemberList *list, int id);
extern int GetConsumableSlotUses(int index);
extern void func_ov052_020d0ee0(int entity, int level, int id, int index, int flag);

void UseFirstAvailableMember(int entity)
{
    int i;
    for (i = 0; i < 2; i++) {
        int index = FindMemberIndexById((MemberList *)(entity + 0x1070), data_ov052_020d20e0[i]);
        if (index != -1 && GetConsumableSlotUses(index) != 0) {
            Member *member = (*(Member ***)(entity + 0x1070))[index];
            func_ov052_020d0ee0(entity, member->level, member->id, index, 0);
            return;
        }
    }
}
