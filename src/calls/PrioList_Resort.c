typedef struct PrioNode {
    struct PrioNode *prev;
    struct PrioNode *next;
    int priority;
} PrioNode;

typedef struct {
    PrioNode *head;
} PrioList;

extern void LinkNodeAtTail(PrioList *list, PrioNode *before, PrioNode *node);

void PrioList_Resort(PrioList *list, PrioNode *node)
{
    PrioNode *cur = list->head;
    PrioNode *last = 0;

    if (cur == node && cur->next == 0) {
        return;
    }
    if (cur == node) {
        list->head = node->next;
    }
    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    }
    for (; cur != 0; cur = cur->next) {
        if (cur->priority < node->priority) {
            LinkNodeAtTail(list, cur, node);
            return;
        }
        last = cur;
    }
    node->prev = last;
    node->next = 0;
    last->next = node;
}
