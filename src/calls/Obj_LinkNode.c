#include "nitro/types.h"

typedef struct TaskObject {
    u32 flags;
    struct TaskObject *parent;
    struct TaskObject *prev;
    struct TaskObject *next;
    u16 classId;
} TaskObject;

typedef struct TaskManager {
    u32 unk_00;
    TaskObject *current;
    u32 frameCount;
    TaskObject *head;
} TaskManager;

extern TaskManager data_020603c8;
extern TaskObject *data_020603d8[];

#pragma push
#pragma opt_common_subs off
void Obj_LinkNode(TaskObject *node)
{
    u32 key = node->classId;
    TaskObject *prev;
    TaskObject *cur;
    TaskObject *next;
    int k;

    if (data_020603c8.head == NULL) {
        data_020603c8.head = node;
        node->prev = NULL;
        node->next = NULL;
        data_020603d8[key] = node;
        return;
    }
    next = NULL;
    prev = NULL;
    cur = data_020603d8[key];
    if (cur != NULL) {
        while ((next = cur->next) != NULL && next->classId == key) {
            cur = next;
        }
        prev = cur;
        goto link;
    }
    for (k = key + 1; k < 0x40; k++) {
        if (data_020603d8[k] != NULL) {
            next = data_020603d8[k];
            break;
        }
    }
    for (k = key - 1; k >= 0; k--) {
        cur = data_020603d8[k];
        if (cur != NULL) {
            TaskObject *following;

            while ((following = cur->next) != NULL && following->classId == k) {
                cur = following;
            }
            prev = cur;
            break;
        }
    }
    data_020603d8[key] = node;
link:
    node->next = next;
    node->prev = prev;
    if (next != NULL) {
        next->prev = node;
    }
    if (prev != NULL) {
        prev->next = node;
    } else {
        data_020603c8.head = node;
    }
}
#pragma pop
