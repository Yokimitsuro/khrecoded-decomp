typedef signed int s32;
typedef unsigned char u8;

typedef struct NNSSndArc {
    u8 reserved[0x9c];
    s32 loadBlockSize;
} NNSSndArc;

extern NNSSndArc *sCurrentSoundArchive;

void NNS_SndArcSetLoadBlockSize(s32 loadBlockSize)
{
    sCurrentSoundArchive->loadBlockSize = loadBlockSize;
}