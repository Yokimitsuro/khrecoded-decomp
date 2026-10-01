typedef signed int s32;
typedef unsigned int u32;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved0[0x64];
    unsigned char file[0x48];
    u32 fileOffset;
} NNSSndStrmPlayer;

extern int FS_SeekFile(void *file, s32 offset, int origin);
extern s32 FS_ReadFile(void *file, void *destination, s32 length);

s32 ReadFileStream(NNSSndStrmPlayer *player, void *destination, u32 size, u32 offset)
{
    int result;
    result = FS_SeekFile(&player->file, (s32)(player->fileOffset + offset), 0);
    return FS_ReadFile(&player->file, destination, (s32)size);
}