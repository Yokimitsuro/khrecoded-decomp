#include "nitro/types.h"
#include "nnsys/g2d.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} GraphicsView;

typedef struct {
    void *fileData;
    GraphicsView view;
} GraphicsResource;

typedef struct {
    u8 pad_000[0x10];
    u16 *archiveFiles[2];
    u8 pad_018[0x134 - 0x18];
    GraphicsResource resources[4];
} MenuScene;

extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType(int bgIndex, NNSG2dScreenData *screen, NNSG2dCharacterData *character,
                                        NNSG2dPaletteData *palette, int mask, int flags);
extern int Gfx_EnqueueTableCmdAt14(int bgIndex, NNSG2dCharacterData *character, u32 offset, u32 size);

void LoadGraphicsResources(MenuScene *scene)
{
    GraphicsResource *resource;

    resource = &scene->resources[0];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], 0xc), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(0, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);

    resource = &scene->resources[1];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[1], 0), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(0, resource->view.character, 0, resource->view.character->szByte);

    resource = &scene->resources[2];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], 0xb), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(6, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);
}
