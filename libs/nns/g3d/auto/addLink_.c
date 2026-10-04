#include "libs/nns/g3d/g3d_kernel_internal.h"

void addLink_(NNSG3dAnmObj **list, NNSG3dAnmObj *item)
{
    if (!*list) {
        *list = item;
    } else if (!(*list)->next) {
        if ((*list)->priority > item->priority) {
            NNSG3dAnmObj *end = item;
            while (end->next) {
                end = end->next;
            }
            end->next = *list;
            *list = item;
        } else {
            (*list)->next = item;
        }
    } else {
        NNSG3dAnmObj *previous = *list;
        NNSG3dAnmObj *current = (*list)->next;

        while (current) {
            if (current->priority >= item->priority) {
                NNSG3dAnmObj *end = item;
                while (end->next) {
                    end = end->next;
                }
                previous->next = item;
                end->next = current;
                return;
            }
            previous = current;
            current = current->next;
        }
        previous->next = item;
    }
}
