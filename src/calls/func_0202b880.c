#include "nitro/types.h"

typedef struct Node {
    struct Node *next;
} Node;

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int gFileLoader;

void func_0202b880(Node *node)
{
    int state = OS_DisableInterrupts();
    node->next = *(Node **)((char *)&gFileLoader + 0x18);
    *(Node **)((char *)&gFileLoader + 0x18) = node;
    OS_RestoreInterrupts(state);
}
