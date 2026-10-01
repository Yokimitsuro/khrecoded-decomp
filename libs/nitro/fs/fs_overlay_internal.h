#ifndef FS_OVERLAY_INTERNAL_H
#define FS_OVERLAY_INTERNAL_H

#include "libs/nitro/fs/fs_internal.h"

typedef int s32;
typedef int MIProcessor;
typedef u32 FSOverlayID;
typedef void (*FSOverlayInitFunction)(void);

enum {
    MI_PROCESSOR_ARM9 = 0,
    MI_PROCESSOR_ARM7 = 1
};

typedef struct CARDRomRegion {
    u32 offset;
    u32 length;
} CARDRomRegion;

typedef struct FSOverlayInfoHeader {
    u32 id;
    u8 *ramAddress;
    u32 ramSize;
    u32 bssSize;
    FSOverlayInitFunction *staticInitializers;
    FSOverlayInitFunction *staticInitializersEnd;
    u32 fileId;
    u32 compressedSize : 24;
    u32 flags : 8;
} FSOverlayInfoHeader;

typedef struct FSOverlayInfo {
    FSOverlayInfoHeader header;
    MIProcessor target;
    CARDRomRegion filePosition;
} FSOverlayInfo;

typedef struct FSOverlaySource {
    FSArchive *archive;
    CARDRomRegion arm9Table;
    CARDRomRegion arm7Table;
    const void *digestKey;
    u32 digestKeyLength;
} FSOverlaySource;

extern FSOverlaySource FSiOverlayContext;

#define FS_OVERLAY_FLAG_COMPRESSED 1
#define FS_OVERLAY_FLAG_AUTHENTICATED 2

static inline u32 FS_GetOverlayTotalSize(const FSOverlayInfo *info)
{
    return info->header.ramSize + info->header.bssSize;
}

static inline u32 FS_GetOverlayImageSize(const FSOverlayInfo *info)
{
    return info->header.ramSize;
}

static inline void *FS_GetOverlayAddress(const FSOverlayInfo *info)
{
    return info->header.ramAddress;
}

FSFileID FS_GetOverlayFileID(const FSOverlayInfo *info);
BOOL FS_LoadOverlayInfo(FSOverlayInfo *info, MIProcessor target,
                        FSOverlayID id);
BOOL FS_LoadOverlayImageAsync(FSOverlayInfo *info, FSFile *file);
BOOL FS_LoadOverlayImage(FSOverlayInfo *info);
void FS_StartOverlay(FSOverlayInfo *info);
void FS_EndOverlay(FSOverlayInfo *info);
BOOL FS_UnloadOverlayImage(FSOverlayInfo *info);

extern BOOL FS_OpenFileFast(FSFile *file, FSFileID id);
extern BOOL FS_CloseFile(FSFile *file);
extern int FS_ReadFile(FSFile *file, void *destination, int length);
extern int FS_ReadFileAsync(FSFile *file, void *destination, int length);
extern u32 FS_GetFileImageTop(const FSFile *file);
extern BOOL FS_CreateFileFromRom(FSFile *file, u32 imageTop, u32 imageBottom);

#endif
