#include "nitro/types.h"

typedef struct {
    int id;
} Member;

typedef struct {
    Member **members;
    int count;
} MemberList;

int FindMemberIndexById(MemberList *list, int id) {
    int result = -1;
    int i;

    for (i = 0; i < list->count; i++) {
        Member *member = list->members[i];

        if (member != NULL && member->id == id) {
            result = i;
            break;
        }
    }
    return result;
}
