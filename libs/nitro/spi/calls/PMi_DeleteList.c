#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PMi_DeleteList(PMGenCallbackInfo **list, PMGenCallbackInfo *info)
{
    OSIntrMode interruptMode;
    PMGenCallbackInfo *current;
    PMGenCallbackInfo *previous;

    if (list == 0) {
        return;
    }

    interruptMode = OS_DisableInterrupts();
    previous = current = *list;
    while (current != 0) {
        if (current == info) {
            if (current == previous) {
                *list = current->next;
            } else {
                previous->next = current->next;
            }
            break;
        }
        previous = current;
        current = current->next;
    }
    (void)OS_RestoreInterrupts(interruptMode);
}
