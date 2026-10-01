#ifndef FS_INTERNAL_H
#define FS_INTERNAL_H

typedef unsigned char u8;
typedef unsigned long u32;
typedef int BOOL;
typedef int FSResult;
typedef u32 FSCommandType;
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
    u8 reserved1[16];
    u8 reserved2[24];
} FSFile;

typedef struct FSArchive {
    u32 name;
    struct FSArchive *next;
    FSFile *list;
    OSThreadQueue queue;
    u32 flags;
    FSCommandType command;
    FSResult result;
    void *userdata;
    const struct FSArchiveInterface *interface;
    u8 reserved[52];
} FSArchive;

#define FS_RESULT_SUCCESS 0
#define FS_RESULT_BUSY 2
#define FS_RESULT_CANCELED 3
#define FS_RESULT_INVALID_PARAMETER 6
#define FS_RESULT_PROC_ASYNC 256

#define FS_COMMAND_ACTIVATE 9UL
#define FS_COMMAND_IDLE 10UL
#define FS_COMMAND_SUSPEND 11UL
#define FS_COMMAND_RESUME 12UL
#define FS_COMMAND_MOUNT 17UL
#define FS_COMMAND_UNMOUNT 18UL
#define FS_COMMAND_MAX 35UL
#define FS_COMMAND_INVALID FS_COMMAND_MAX

#define FS_FILE_STATUS_BUSY 0x00000001UL
#define FS_FILE_STATUS_CANCEL 0x00000002UL
#define FS_FILE_STATUS_BLOCKING 0x00000004UL
#define FS_FILE_STATUS_ASYNC_DONE 0x00000008UL
#define FS_FILE_STATUS_OPERATING 0x00000040UL
#define FS_FILE_STATUS_UNICODE_MODE 0x00000080UL
#define FS_FILE_STATUS_CMD_SHIFT 8UL
#define FS_FILE_STATUS_CMD_MASK 0x000000ffUL

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(OSThreadQueue *queue);
extern void OS_WakeupThread(OSThreadQueue *queue);

BOOL FSi_IsEventCommand(FSCommandType command);
void FSi_EndCommand(FSFile *file, FSResult result);
FSResult FSi_WaitForArchiveCompletion(FSFile *file, FSResult result);
FSResult FSi_InvokeCommand(FSFile *file, FSCommandType command);
FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner);
void FSi_ExecuteAsyncCommand(FSFile *file);
void FSi_ExecuteSyncCommand(FSFile *file);
void FS_InitFile(FSFile *file);

static inline FSCommandType FSi_GetCurrentCommand(const FSFile *file)
{
    return (file->status >> FS_FILE_STATUS_CMD_SHIFT) & FS_FILE_STATUS_CMD_MASK;
}

static inline void FSi_WaitConditionOn(u32 *flags, u32 bits,
                                       OSThreadQueue *queue)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    while ((*flags & bits) == 0) {
        OS_SleepThread(queue);
    }
    (void)OS_RestoreInterrupts(interruptState);
}

#endif