#include "nitro/types.h"

typedef struct {
    u8 pad0[0x3d];
    s8 kind;
} MemberInfo;

typedef struct {
    u8 pad0[0x50];
    MemberInfo *info;
} Member;

extern unsigned int GetMemberValue(int *container, int index);
extern Member *GetMemberByIndex(int *container, int index);
extern BOOL func_ov021_020ae748(MemberInfo *counter);

BOOL CanUseMemberSlot(int entity, int index)
{
    BOOL result = TRUE;
    Member *member;
    switch (GetMemberValue((int *)(entity + 0x1070), index)) {
    case 1:
        if (*(int *)(entity + 0x1078) != 0) {
            result = FALSE;
        }
        break;
    case 2:
        member = GetMemberByIndex((int *)(entity + 0x1070), index);
        result = func_ov021_020ae748(member->info);
        if (result && member->info->kind == 3 && *(int *)(entity + 0x1078) != 0) {
            result = FALSE;
        }
        break;
    case 4:
        if (*(int *)(entity + 0x1078) != 0 && *(int *)(*(int *)(entity + 0x1078) + 4) == 4) {
            result = FALSE;
        }
        break;
    }
    return result;
}
