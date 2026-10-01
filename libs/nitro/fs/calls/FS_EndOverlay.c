#include "libs/nitro/fs/fs_overlay_internal.h"

typedef void (*DestructorFunction)(void *object);

typedef struct DestructorChain {
    struct DestructorChain *next;
    DestructorFunction destructor;
    void *object;
} DestructorChain;

extern DestructorChain *__global_destructor_chain;

void FS_EndOverlay(FSOverlayInfo *info)
{
    for (;;) {
        DestructorChain *head = 0;
        DestructorChain *tail = 0;
        u32 regionTop = (u32)FS_GetOverlayAddress(info);
        u32 regionBottom = regionTop + FS_GetOverlayTotalSize(info);

        {
            OSIntrMode interruptState = OS_DisableInterrupts();
            DestructorChain *previous = 0;
            DestructorChain *base = __global_destructor_chain;
            DestructorChain *current = base;

            while (current) {
                DestructorChain *next = current->next;
                u32 destructor = (u32)current->destructor;
                u32 object = (u32)current->object;

                if (((object == 0) && (destructor >= regionTop) &&
                     (destructor < regionBottom)) ||
                    ((object >= regionTop) && (object < regionBottom))) {
                    if (!tail) {
                        head = current;
                    } else {
                        tail->next = current;
                    }
                    if (base == current) {
                        base = __global_destructor_chain = next;
                    }
                    tail = current;
                    current->next = 0;
                    if (previous) {
                        previous->next = next;
                    }
                } else {
                    previous = current;
                }
                current = next;
            }
            (void)OS_RestoreInterrupts(interruptState);
        }

        if (!head) {
            break;
        }

        do {
            DestructorChain *next = head->next;

            if (head->destructor) {
                head->destructor(head->object);
            }
            head = next;
        } while (head);
    }
}
