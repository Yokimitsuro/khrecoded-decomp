#ifndef NNS_SNDARC_INTERNAL_H
#define NNS_SNDARC_INTERNAL_H

#include "libs/nitro/fs/fs_internal.h"

typedef int s32;
typedef struct NNSSndHeap *NNSSndHeapHandle;
typedef void (*NNSSndHeapDisposeCallback)(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);

#ifndef NULL
#define NULL ((void *)0)
#endif
#define TRUE 1
#define FALSE 0
#define NNS_SND_HEAP_INVALID_HANDLE ((NNSSndHeapHandle)NULL)

typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;

typedef struct SNDBinaryBlockHeader {
    u32 kind;
    u32 size;
} SNDBinaryBlockHeader;

typedef struct NNSSndArcFileInfo {
    u32 offset;
    u32 size;
    void *memory;
    u32 reserved;
} NNSSndArcFileInfo;

typedef struct NNSSndArcFat {
    SNDBinaryBlockHeader blockHeader;
    u32 count;
    NNSSndArcFileInfo files[1];
} NNSSndArcFat;

typedef struct NNSSndArcInfo {
    SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerInfoOffset;
    u32 groupInfoOffset;
    u32 strmPlayerInfoOffset;
    u32 strmOffset;
} NNSSndArcInfo;

typedef struct NNSSndArcSymbol {
    SNDBinaryBlockHeader blockHeader;
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerOffset;
    u32 groupOffset;
    u32 strmPlayerOffset;
    u32 strmOffset;
} NNSSndArcSymbol;

typedef struct NNSSndArcOffsetTable {
    u32 count;
    u32 offsets[1];
} NNSSndArcOffsetTable;

typedef struct NNSSndArcSeqArcSymbolEntry {
    u32 symbolOffset;
    u32 tableOffset;
} NNSSndArcSeqArcSymbolEntry;

typedef struct NNSSndArcSeqArcSymbolTable {
    u32 count;
    NNSSndArcSeqArcSymbolEntry entries[1];
} NNSSndArcSeqArcSymbolTable;

typedef struct NNSSndArcSeqArcInfo {
    u32 fileId;
} NNSSndArcSeqArcInfo;

typedef struct NNSSndSeqParam {
    u16 bankNo;
    u8 volume;
    u8 channelPrio;
    u8 playerPrio;
    u8 playerNo;
    u16 reserved;
} NNSSndSeqParam;

typedef struct NNSSndSeqArcSeqInfo {
    u32 offset;
    NNSSndSeqParam param;
} NNSSndSeqArcSeqInfo;

typedef struct NNSSndSeqArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 count;
    NNSSndSeqArcSeqInfo info[1];
} NNSSndSeqArc;

typedef struct NNSSndArcHeader {
    SNDBinaryFileHeader fileHeader;
    u32 symbolDataOffset;
    u32 symbolDataSize;
    u32 infoOffset;
    u32 infoSize;
    u32 fatOffset;
    u32 fatSize;
    u32 fileImageOffset;
    u32 fileImageSize;
} NNSSndArcHeader;

typedef struct NNSSndArc {
    NNSSndArcHeader header;
    BOOL fileOpen;
    FSFile file;
    FSFileID fileId;
    u32 reservedAfterFileId[3];
    NNSSndArcFat *fat;
    NNSSndArcSymbol *symbol;
    NNSSndArcInfo *info;
    s32 loadBlockSize;
} NNSSndArc;

enum {
    FS_SEEK_SET = 0
};

extern NNSSndArc *sCurrentSoundArchive;
extern char sNullSoundArchiveSymbol[4];

extern BOOL FS_ConvertPathToFileID(FSFileID *fileId, const char *path);
extern BOOL FS_OpenFileFast(FSFile *file, FSFileID fileId);
extern int FS_ReadFile(FSFile *file, void *destination, int length);
extern int FS_SeekFile(FSFile *file, int offset, int origin);
extern void *NNS_SndHeapAlloc(
    NNSSndHeapHandle heap,
    u32 size,
    NNSSndHeapDisposeCallback callback,
    u32 data1,
    u32 data2);
extern const NNSSndArcSeqArcInfo *NNS_SndArcGetSeqArcInfo(int seqArcNo);
extern void *NNS_SndArcGetFileAddress(u32 fileId);
extern u32 NNSi_SndSeqArcGetSeqCount(const NNSSndSeqArc *seqArc);
extern const char *GetSoundArchiveSymbol(
    const NNSSndArcOffsetTable *table,
    int index,
    const void *base);

#endif
