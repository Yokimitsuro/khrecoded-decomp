#ifndef FS_INTERNAL_H
#define FS_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int FSResult;
typedef u32 FSCommandType;
typedef u32 OSIntrMode;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

struct FSArchive;

typedef struct FSDirPos {
    struct FSArchive *archive;
    u16 ownId;
    u16 index;
    u32 position;
} FSDirPos;

typedef struct FSFileID {
    struct FSArchive *archive;
    u32 fileId;
} FSFileID;

typedef struct FSROMFATFileProperty {
    u32 ownId;
    u32 top;
    u32 bottom;
    u32 position;
} FSROMFATFileProperty;

typedef struct FSROMFATDirProperty {
    FSDirPos position;
    u32 parent;
} FSROMFATDirProperty;

typedef union FSROMFATProperty {
    FSROMFATFileProperty file;
    FSROMFATDirProperty directory;
} FSROMFATProperty;

typedef struct FSReadFileInfo {
    void *destination;
    u32 originalLength;
    u32 length;
} FSReadFileInfo;

typedef struct FSWriteFileInfo {
    const void *source;
    u32 originalLength;
    u32 length;
} FSWriteFileInfo;

typedef struct FSSeekDirInfo {
    FSDirPos position;
} FSSeekDirInfo;

typedef struct FSFindPathInfo {
    FSDirPos position;
    const char *path;
    BOOL findDirectory;
    union {
        FSFileID *file;
        FSDirPos *directory;
    } result;
} FSFindPathInfo;

typedef struct FSGetPathInfo {
    u8 *buffer;
    u32 bufferLength;
    u16 totalLength;
    u16 directoryId;
} FSGetPathInfo;

typedef struct FSOpenFileFastInfo {
    FSFileID id;
} FSOpenFileFastInfo;

typedef struct FSOpenFileDirectInfo {
    u32 top;
    u32 bottom;
    u32 index;
} FSOpenFileDirectInfo;

typedef union FSROMFATCommandInfo {
    FSReadFileInfo readFile;
    FSWriteFileInfo writeFile;
    FSSeekDirInfo seekDirectory;
    FSFindPathInfo findPath;
    FSGetPathInfo getPath;
    FSOpenFileFastInfo openFileFast;
    FSOpenFileDirectInfo openFileDirect;
} FSROMFATCommandInfo;

typedef struct FSROMFATArchiveContext {
    u32 base;
    u32 fat;
    u32 fatSize;
    u32 fnt;
    u32 fntSize;
    u32 fatBackup;
    u32 fntBackup;
    void *loadedTables;
    void *readFunction;
    void *writeFunction;
    u8 reserved[4];
    void *procedure;
    u32 procedureFlags;
} FSROMFATArchiveContext;

typedef struct FSArchiveResource {
    u64 totalSize;
    u64 availableSize;
    u32 maxFileHandles;
    u32 currentFileHandles;
    u32 maxDirectoryHandles;
    u32 currentDirectoryHandles;
    u32 bytesPerSector;
    u32 sectorsPerCluster;
    u32 totalClusters;
    u32 availableClusters;
} FSArchiveResource;

typedef void (*FSArchiveMethod)(void);

typedef struct FSArchiveInterface {
    FSArchiveMethod readFile;
    FSArchiveMethod writeFile;
    FSArchiveMethod seekDirectory;
    FSArchiveMethod readDirectory;
    FSArchiveMethod findPath;
    FSArchiveMethod getPath;
    FSArchiveMethod openFileFast;
    FSArchiveMethod openFileDirect;
    FSArchiveMethod closeFile;
    FSArchiveMethod activate;
    FSArchiveMethod idle;
    FSArchiveMethod suspend;
    FSArchiveMethod resume;
    FSArchiveMethod openFile;
    FSArchiveMethod seekFile;
    FSArchiveMethod getFileLength;
    FSArchiveMethod getFilePosition;
    FSArchiveMethod mount;
    FSArchiveMethod unmount;
    FSArchiveMethod getArchiveCaps;
    FSArchiveMethod createFile;
    FSArchiveMethod deleteFile;
    FSArchiveMethod renameFile;
    FSArchiveMethod getPathInfo;
    FSArchiveMethod setPathInfo;
    FSArchiveMethod createDirectory;
    FSArchiveMethod deleteDirectory;
    FSArchiveMethod renameDirectory;
    FSArchiveMethod getArchiveResource;
    FSArchiveMethod unused29;
    FSArchiveMethod flushFile;
    FSArchiveMethod setFileLength;
    FSArchiveMethod openDirectory;
    FSArchiveMethod closeDirectory;
    FSArchiveMethod setSeekCache;
    u8 reserved[116];
} FSArchiveInterface;

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

typedef struct FSRomArchiveState {
    u32 defaultDmaNo;
    int cardLockId;
    FSArchive archive;
} FSRomArchiveState;

extern FSRomArchiveState fsi_rom_archive_state;

#define FS_RESULT_SUCCESS 0
#define FS_RESULT_BUSY 2
#define FS_RESULT_CANCELED 3
#define FS_RESULT_UNSUPPORTED 4
#define FS_RESULT_INVALID_PARAMETER 6
#define FS_RESULT_PROC_ASYNC 256
#define FS_RESULT_PROC_UNKNOWN 258

#define FS_COMMAND_READFILE 0UL
#define FS_COMMAND_WRITEFILE 1UL
#define FS_COMMAND_SEEKDIR 2UL
#define FS_COMMAND_READDIR 3UL
#define FS_COMMAND_FINDPATH 4UL
#define FS_COMMAND_GETPATH 5UL
#define FS_COMMAND_OPENFILEFAST 6UL
#define FS_COMMAND_OPENFILEDIRECT 7UL
#define FS_COMMAND_CLOSEFILE 8UL
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
#define FS_FILE_STATUS_IS_FILE 0x00000010UL
#define FS_FILE_STATUS_IS_DIRECTORY 0x00000020UL
#define FS_FILE_STATUS_OPERATING 0x00000040UL
#define FS_FILE_STATUS_UNICODE_MODE 0x00000080UL
#define FS_FILE_STATUS_CMD_SHIFT 8UL
#define FS_FILE_STATUS_CMD_MASK 0x000000ffUL

#define FS_ARCHIVE_FLAG_TABLE_LOAD 0x00000004UL

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
void FS_CancelFile(FSFile *file);
BOOL FSi_SendCommand(FSFile *file, FSCommandType command, BOOL blocking);
FSArchive *FS_NormalizePath(const char *path, u32 *baseId, char *relativePath);
BOOL FSi_GetFileLengthIfProc(FSFile *file, u32 *length);
u32 FS_GetFileLength(FSFile *file);
BOOL FSi_GetFilePositionIfProc(FSFile *file, u32 *position);
FSResult FSi_ROMFAT_GetArchiveCaps(FSArchive *archive, u32 *capabilities);
BOOL FS_OpenFileEx(FSFile *file, const char *path, u32 mode);
BOOL FS_OpenFile(FSFile *file, const char *path);
u32 FS_GetLength(FSFile *file);
FSResult FSi_TranslateCommand(FSFile *file, FSCommandType command,
                              BOOL blocking);
FSResult FSi_ROMFAT_ReadFile(FSArchive *archive, FSFile *file, void *buffer,
                             u32 *length);
FSResult FSi_ROMFAT_WriteFile(FSArchive *archive, FSFile *file,
                              const void *buffer, u32 *length);
FSResult FSi_ROMFAT_SeekDirectory(FSArchive *archive, FSFile *file, u32 id,
                                  u32 position);
FSResult FSi_ROMFAT_FindPath(FSArchive *archive, u32 baseDirectoryId,
                             const char *path, u32 *targetId,
                             BOOL targetIsDirectory);
FSResult FSi_ROMFAT_GetPath(FSArchive *archive, FSFile *file,
                            BOOL isDirectory, char *buffer, u32 *length);
FSResult FSi_ROMFAT_OpenFileFast(FSArchive *archive, FSFile *file, u32 id,
                                 u32 mode);
FSResult FSi_ROMFAT_OpenFileDirect(FSArchive *archive, FSFile *file, u32 top,
                                   u32 bottom, u32 *id);
FSResult FSi_ROMFAT_CloseFile(FSArchive *archive, FSFile *file);
FSResult FSi_ROMFAT_OpenFile(FSArchive *archive, FSFile *file, u32 baseId,
                             const char *path, u32 mode);
FSResult FSi_ROMFAT_SeekFile(FSArchive *archive, FSFile *file, int *offset,
                             int origin);
FSResult FSi_ROMFAT_GetFileLength(FSArchive *archive, FSFile *file,
                                  u32 *length);
FSResult FSi_ROMFAT_GetFilePosition(FSArchive *archive, FSFile *file,
                                    u32 *position);
FSResult FSi_ROMFAT_OpenDirectory(FSArchive *archive, FSFile *file, u32 baseId,
                                  const char *path, u32 mode);
FSResult FSi_ROMFAT_CloseDirectory(FSArchive *archive, FSFile *file);
FSResult FSi_ROMFAT_GetArchiveResource(FSArchive *archive,
                                       FSArchiveResource *resource);
u32 FS_GetArchiveOffset(const FSArchive *archive, u32 position);
BOOL FS_IsArchiveTableLoaded(volatile const FSArchive *archive);
u32 FS_GetFileImageTop(const FSFile *file);
BOOL FSi_IsUnreadableRomOffset(FSArchive *archive, u32 offset);
FSResult FSi_EmptyArchiveProc(FSFile *file, FSCommandType command);
FSResult FSi_ReadDummyCallback(FSArchive *archive, void *destination,
                               u32 source, u32 length);
FSResult FSi_WriteDummyCallback(FSArchive *archive, const void *source,
                                u32 destination, u32 length);
BOOL FSi_OverrideRomArchive(FSArchive *archive);

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