#include "libs/nitro/os/os_mutex_internal.h"

#define NULL ((void *)0)

void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread)
{
    OSThread *after;
    OSThread *before;

    for (after = queue->head;
         after != NULL && after->priority <= thread->priority;
         after = after->link.next) {
        if (after == thread) {
            return;
        }
    }

    if (after == NULL) {
        before = queue->tail;
        if (before == NULL) {
            queue->head = thread;
        } else {
            before->link.next = thread;
        }
        thread->link.prev = before;
        thread->link.next = NULL;
        queue->tail = thread;
        return;
    }

    before = after->link.prev;
    if (before == NULL) {
        queue->head = thread;
    } else {
        before->link.next = thread;
    }
    thread->link.prev = before;
    thread->link.next = after;
    after->link.prev = thread;
}