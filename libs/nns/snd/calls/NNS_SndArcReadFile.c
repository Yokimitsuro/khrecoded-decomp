typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct NNSSndArcFileInfo {
    u32 offset;
    u32 size;
    void *memory;
    u32 reserved;
} NNSSndArcFileInfo;

typedef struct NNSSndArcFat {
    u8 header[8];
    u32 count;
    NNSSndArcFileInfo files[1];
} NNSSndArcFat;

typedef struct NNSSndArc {
    u8 headerAndState[0x34];
    u8 file[0x5c];
    NNSSndArcFat *fat;
    void *symbol;
    void *info;
    s32 loadBlockSize;
} NNSSndArc;

extern NNSSndArc *sCurrentSoundArchive;
extern int FS_SeekFile(void *file, s32 offset, int origin);
extern void FSi_WaitForCardThread(void);
extern s32 FS_ReadFile(void *file, void *destination, s32 length);

s32 NNS_SndArcReadFile(u32 fileId, void *buffer, s32 size, s32 offset)
{
    NNSSndArc *arc = sCurrentSoundArchive;
    const NNSSndArcFileInfo *file;
    s32 totalReadSize;
    s32 readSize;
    s32 blockSize;
    s32 currentOffset;
    s32 requestSize;
    u8 *destination;

    if (fileId >= arc->fat->count) return -1;
    file = &arc->fat->files[fileId];
    currentOffset = offset;
    blockSize = arc->loadBlockSize;
    if (blockSize == 0) {
        blockSize = size;
    }
    totalReadSize = 0;
    destination = (u8 *)buffer;

    while (totalReadSize < size) {
        requestSize = size - totalReadSize;
        if (requestSize > blockSize) requestSize = blockSize;
        if (requestSize > file->size - currentOffset) {
            requestSize = (s32)(file->size - currentOffset);
        }
        if (requestSize == 0) break;

        if (!FS_SeekFile(&arc->file, (s32)(file->offset + currentOffset), 0)) {
            return -1;
        }
        FSi_WaitForCardThread();
        readSize = FS_ReadFile(&arc->file, destination, requestSize);
        if (readSize < 0) return readSize;

        totalReadSize += readSize;
        currentOffset += readSize;
        destination += readSize;
    }

    return totalReadSize;
}