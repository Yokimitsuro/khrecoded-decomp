typedef unsigned long u32;
typedef int BOOL;
typedef int FSResult;
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
    FSResult error;
    OSThreadQueue queue[1];
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
} FSArchive;

#define FS_FILE_STATUS_BLOCKING 0x00000004UL
#define FS_FILE_STATUS_ASYNC_DONE 0x00000008UL

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void FSi_EndCommand(FSFile *file, FSResult result);
extern FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner);
extern void FSi_ExecuteAsyncCommand(FSFile *file);

void FS_NotifyArchiveAsyncEnd(FSArchive *archive, FSResult result)
{
    FSFile *file = archive->list;

    if (file->status & FS_FILE_STATUS_BLOCKING) {
        OSIntrMode interruptState = OS_DisableInterrupts();
        file->status |= FS_FILE_STATUS_ASYNC_DONE;
        file->error = result;
        OS_WakeupThread(file->queue);
        (void)OS_RestoreInterrupts(interruptState);
    } else {
        FSi_EndCommand(file, result);
        file = FSi_NextCommand(archive, 1);
        if (file) {
            FSi_ExecuteAsyncCommand(file);
        }
    }
}