#include "libs/nns/g3d/g3d_kernel_internal.h"

BOOL removeLink_(NNSG3dAnmObj **list, NNSG3dAnmObj *item)
{
    NNSG3dAnmObj *current;
    NNSG3dAnmObj *previous;

    if (!*list) {
        return FALSE;
    }

    if (*list == item) {
        *list = (*list)->next;
        item->next = NULL;
        return TRUE;
    }

    current = (*list)->next;
    previous = *list;
    while (current) {
        if (current == item) {
            previous->next = current->next;
            current->next = NULL;
            return TRUE;
        }
        previous = current;
        current = current->next;
    }
    return FALSE;
}
