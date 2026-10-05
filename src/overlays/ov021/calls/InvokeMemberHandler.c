#include "nitro/types.h"

typedef struct Member Member;
typedef int (*MemberHandler)(Member *member, int arg);

struct Member {
    u8 pad00[0x34];
    MemberHandler handler;
};

typedef struct MemberList {
    Member **members;
    s32 count;
    Member *current;
} MemberList;

int InvokeMemberHandler(MemberList *list, int index, int arg)
{
    Member *member = NULL;
    int result = 0;

    if (index >= 0) {
        if (index < list->count) {
            member = list->members[index];
        }
    } else {
        member = list->current;
    }
    if (member != NULL && member->handler != NULL) {
        result = member->handler(member, arg);
    }
    return result;
}
