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
    u8 reserved[0x90];
    NNSSndArcFat *fat;
} NNSSndArc;

extern NNSSndArc *sCurrentSoundArchive;

void *NNS_SndArcGetFileAddress(u32 fileId)
{
    NNSSndArc *arc = sCurrentSoundArchive;
    if (fileId >= arc->fat->count) return 0;
    return arc->fat->files[fileId].memory;
}