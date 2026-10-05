#include "nitro/types.h"

typedef struct CallbackSlot {
    u8 pad_000[0x820];
    void (*callback)(void *arg);
    void *argument;
} CallbackSlot;

typedef struct FieldContext {
    u8 pad_0000[0x1f10];
    CallbackSlot pending;
} FieldContext;

void RunPendingCallback(FieldContext *context)
{
    CallbackSlot *slot = &context->pending;
    void (*callback)(void *arg) = slot->callback;
    void *argument;

    if (callback != NULL) {
        argument = slot->argument;
        slot->callback = NULL;
        slot->argument = NULL;
        callback(argument);
    }
}
