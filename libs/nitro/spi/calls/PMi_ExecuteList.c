#include "libs/nitro/spi/calls/pm_callback_internal.h"

void PMi_ExecuteList(PMGenCallbackInfo *list)
{
    while (list != 0) {
        list->callback(list->argument);
        list = list->next;
    }
}
