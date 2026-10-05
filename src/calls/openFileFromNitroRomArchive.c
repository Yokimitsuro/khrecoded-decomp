typedef int BOOL;
typedef int s32;
typedef short s16;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;
typedef struct FSFileID FSFileID;

extern BOOL FS_OpenFileDirect(FSFile *file, FSArchive *archive, u32 image_top, u32 image_bot, FSFileID *fileId);

BOOL openFileFromNitroRomArchive(FSFile *file, u32 fileId)
{
    u32 archiveIdMask = 0x00fffffc;
    u32 romArchiveBase = ((fileId >> 7) & archiveIdMask) + 0x01ff8000;
    u16 fileIndex  = (u16)(fileId & (archiveIdMask >> 15));
    u8 *archiveHeader = (u8 *)romArchiveBase;
    u32 fileStart = *(u32 *)(archiveHeader + 0xc) + ((u32)*(u16 *)(archiveHeader + fileIndex * 2 + 0x10) << 9);
    FSArchive *archive = *(FSArchive **)(archiveHeader + 8);
    s32 fatEntryCountHalf = (s32)((*(u16 *)(archiveHeader + 2) & (archiveIdMask >> 15)) + 1) / 2;
    u8 *fatTable = archiveHeader + (u32)((u16)(fatEntryCountHalf * 2)) * 2;
    u32 storedFileLength = *(u32 *)(fatTable + fileIndex * 4 + 0x10) & 0x7fffffff;
    return FS_OpenFileDirect(file, archive, fileStart, fileStart + storedFileLength, (FSFileID *)0);
}
