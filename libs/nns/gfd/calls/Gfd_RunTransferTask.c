typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSGfdVramTransferTask {
    u32 type;
    const void *source;
    u32 destination;
    u32 size;
} NNSGfdVramTransferTask;

typedef int (*NNSGfdVramTransferHandler)(
    const void *source,
    u32 destination,
    u32 size
);

extern NNSGfdVramTransferHandler sVramTransferTaskHandlers[];
extern void DC_FlushRange(const void *address, u32 size);

int Gfd_RunTransferTask(
    const NNSGfdVramTransferTask *task,
    BOOL flushSource
)
{
    NNSGfdVramTransferHandler handler;

    handler = sVramTransferTaskHandlers[task->type];
    if (flushSource) {
        DC_FlushRange(task->source, task->size);
    }

    return handler(task->source, task->destination, task->size);
}
