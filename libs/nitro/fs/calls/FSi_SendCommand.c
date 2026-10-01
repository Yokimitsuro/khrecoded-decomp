typedef unsigned long u32;
typedef int BOOL;
typedef int FSCommandType;
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
    OSThreadQueue queue;
    u32 flags;
} FSArchive;

#define FS_RESULT_BUSY 2
#define FS_RESULT_CANCELED 3
#define FS_RESULT_INVALID_PARAMETER 6
#define FS_FILE_STATUS_BUSY 0x00000001UL
#define FS_FILE_STATUS_BLOCKING 0x00000004UL
#define FS_FILE_STATUS_CMD_SHIFT 8UL
#define FS_FILE_STATUS_CMD_MASK 0x000000FFUL
#define FS_ARCHIVE_FLAG_RUNNING 0x00000010UL
#define FS_ARCHIVE_FLAG_UNLOADING 0x00000080UL

extern void OS_Terminate(void);
#define OS_TPanic(...) OS_Terminate()
#define OS_TWarning(...) ((void)0)
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void FSi_EndCommand(FSFile *file, FSResult result);
extern FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner);
extern void FSi_ExecuteSyncCommand(FSFile *file);
extern void FSi_ExecuteAsyncCommand(FSFile *file);

static inline BOOL FS_IsBusy(volatile const FSFile *file)
{
    return (file->status & FS_FILE_STATUS_BUSY) != 0;
}

static inline BOOL FS_IsSucceeded(volatile const FSFile *file)
{
    return file->error == 0;
}

BOOL FSi_SendCommand(FSFile *file, FSCommandType command, BOOL blocking)
{
    BOOL result = 0;
    FSArchive *const archive = file->archive;
    BOOL owner = 0;

    if (FS_IsBusy(file)) {
        OS_TPanic("file busy");
    }
    if (!archive) {
        OS_TWarning("file has no archive");
        file->error = FS_RESULT_INVALID_PARAMETER;
        return 0;
    }

    file->error = FS_RESULT_BUSY;
    file->status &= ~(FS_FILE_STATUS_CMD_MASK << FS_FILE_STATUS_CMD_SHIFT);
    file->status |= command << FS_FILE_STATUS_CMD_SHIFT;
    file->status |= FS_FILE_STATUS_BUSY;
    file->next = 0;
    if (blocking) {
        file->status |= FS_FILE_STATUS_BLOCKING;
    }

    {
        OSIntrMode interruptState = OS_DisableInterrupts();
        if (archive->flags & FS_ARCHIVE_FLAG_UNLOADING) {
            FSi_EndCommand(file, FS_RESULT_CANCELED);
        } else {
            FSFile **link;
            for (link = &archive->list; *link; link = &(*link)->next) {
            }
            *link = file;
        }
        owner = archive->list == file &&
                !(archive->flags & FS_ARCHIVE_FLAG_RUNNING);
        (void)OS_RestoreInterrupts(interruptState);
    }

    if (file->error != FS_RESULT_CANCELED) {
        FSFile *next = FSi_NextCommand(archive, owner);
        if (blocking) {
            FSi_ExecuteSyncCommand(file);
            result = FS_IsSucceeded(file);
        } else {
            if (next) {
                FSi_ExecuteAsyncCommand(next);
            }
            result = 1;
        }
    }

    return result;
}