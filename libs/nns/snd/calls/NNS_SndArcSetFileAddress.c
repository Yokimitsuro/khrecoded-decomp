typedef unsigned int u32;

typedef struct NNSSndArcFatFile {
    void *memory;
    unsigned char padding04[0x0c];
} NNSSndArcFatFile;

typedef struct NNSSndArcFat {
    unsigned char padding00[0x14];
    NNSSndArcFatFile files[1];
} NNSSndArcFat;

typedef struct NNSSndArc {
    unsigned char padding00[0x90];
    NNSSndArcFat *fat;
} NNSSndArc;

extern NNSSndArc *sCurrentSoundArchive;

void NNS_SndArcSetFileAddress(u32 fileId, void *address)
{
    sCurrentSoundArchive->fat->files[fileId].memory = address;
}