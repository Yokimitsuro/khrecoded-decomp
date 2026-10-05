#include "nitro/types.h"

typedef struct Node Node;

struct Node {
    Node *next;
    u8 pad_04[0x30 - 4];
    u16 flags;
    u8 tag;
};

typedef struct {
    u8 pad_00[6];
    u16 count;
    Node *head;
    Node *tail;
} NodeList;

extern NodeList *data_ov001_020a04fc;
extern Node *func_ov001_0208724c(u32 param1, u32 param2);

void AppendNodeToActiveList(u32 param1, u32 param2, u8 tag) {
    Node *node = func_ov001_0208724c(param1, param2);
    NodeList *list = data_ov001_020a04fc;
    node->flags |= 2;
    node->next = NULL;
    if (list->tail != NULL) {
        list->tail->next = node;
    }
    if (list->head == NULL) {
        list->head = node;
    }
    node->tag = tag;
    list->tail = node;
    list->count++;
}
