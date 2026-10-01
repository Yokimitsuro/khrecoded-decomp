#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PMi_InsertList(
    PMGenCallbackInfo **list,
    PMGenCallbackInfo *info,
    int priority,
    int method)
{
    OSIntrMode interruptMode;
    PMGenCallbackInfo *current;
    PMGenCallbackInfo *previous;

    if (list == 0) {
        return;
    }

    info->priority = priority;
    interruptMode = OS_DisableInterrupts();
    current = *list;
    previous = 0;

    while (current != 0) {
        if (method == PMi_COMPARE_GT && current->priority > priority) {
            break;
        }
        if (method == PMi_COMPARE_GE && current->priority >= priority) {
            break;
        }
        previous = current;
        current = current->next;
    }

    if (current != 0) {
        info->next = current;
    } else {
        info->next = 0;
    }

    if (previous != 0) {
        previous->next = info;
    } else {
        *list = info;
    }

    (void)OS_RestoreInterrupts(interruptMode);
}
