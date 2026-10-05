#include "nitro/types.h"

typedef struct TaskBody TaskBody;

struct TaskBody {
    u8 pad_00[8];
    void (*deactivate)(TaskBody *body);
};

typedef struct TaskNode {
    struct TaskNode *prev;
    struct TaskNode *next;
    TaskBody body;
    u8 pad_14[0x3e];
    u8 flags;
} TaskNode;

typedef struct TaskManager {
    u16 activeIds[8];
} TaskManager;

extern TaskManager *data_ov001_020a0498;
extern TaskNode *func_ov001_02069014(TaskManager *manager, u16 id);

void DeactivateTaskById(int id)
{
    TaskManager *manager = data_ov001_020a0498;
    TaskNode *node = func_ov001_02069014(manager, id);
    TaskBody *body;
    int slot;

    node->flags &= 0xfe;
    body = &node->body;
    body->deactivate(body);
    for (slot = 0; slot < 8; slot++) {
        if (id == manager->activeIds[slot]) {
            manager->activeIds[slot] = 0xffff;
        }
    }
}
