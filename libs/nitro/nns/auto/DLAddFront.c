struct DLNode {
    struct DLNode *prev;
    struct DLNode *next;
};

struct DLNode *DLAddFront(struct DLNode *head, struct DLNode *node)
{
    struct DLNode *none = 0;

    node->next = head;
    node->prev = none;
    if (head != 0) {
        head->prev = node;
    }
    return node;
}