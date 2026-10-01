typedef unsigned long u32;
typedef int BOOL;
typedef u32 OSIntrMode;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct FSFile {
    struct FSFile *next;
    void *userdata;
    struct FSArchive *archive;
    u32 status;
    void *argument;
    int error;
    OSThreadQueue queue[1];
} FSFile;

#define FS_FILE_STATUS_BUSY 0x00000001UL
#define FS_FILE_STATUS_BLOCKING 0x00000004UL
#define FS_FILE_STATUS_OPERATING 0x00000040UL

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void FSi_ExecuteSyncCommand(FSFile *file);

static inline BOOL FS_IsBusy(volatile const FSFile *file)
{
    return (file->status & FS_FILE_STATUS_BUSY) != 0;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile *file)
{
    return file->error == 0;
}

static inline void FSi_WaitConditionChange(u32 *flags, u32 on, u32 off,
                                           OSThreadQueue *queue)
{
    OSIntrMode interruptState = OS_DisableInterrupts();
    while ((!on || ((*flags & on) == 0)) &&
           (!off || ((*flags & off) != 0))) {
        OS_SleepThread(queue);
    }
    (void)OS_RestoreInterrupts(interruptState);
}

static inline void FSi_WaitConditionOff(u32 *flags, u32 bits,
                                        OSThreadQueue *queue)
{
    FSi_WaitConditionChange(flags, 0, bits, queue);
}

BOOL FS_WaitAsync(FSFile *file)
{
    BOOL isOwner = 0;
    OSIntrMode interruptState = OS_DisableInterrupts();

    if (FS_IsBusy(file)) {
        isOwner = !(file->status &
                    (FS_FILE_STATUS_BLOCKING | FS_FILE_STATUS_OPERATING));
        if (isOwner) {
            file->status |= FS_FILE_STATUS_BLOCKING;
        }
    }

    (void)OS_RestoreInterrupts(interruptState);
    if (isOwner) {
        FSi_ExecuteSyncCommand(file);
    } else {
        FSi_WaitConditionOff(&file->status, FS_FILE_STATUS_BUSY, file->queue);
    }

    return FS_IsSucceeded(file);
}