#include "nitro/types.h"
#include "nnsys/g2d.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

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
    u8 pad_00[4];
    u16 *archiveFiles[2];
    u8 pad_0c[0xa4 - 0xc];
    GraphicsResource resources[5];
    u8 pad_f4[0xcc7c - 0xf4];
    BOOL altLayout;
} MenuScene;

extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(GraphicsView *view, void *file, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType(int bgIndex, NNSG2dScreenData *screen, NNSG2dCharacterData *character,
                                        NNSG2dPaletteData *palette, int mask, int flags);
extern int Gfx_EnqueueTableCmdAt14(int bgIndex, NNSG2dCharacterData *character, u32 offset, u32 size);

void LoadMenuGraphics(MenuScene *scene)
{
    GraphicsResource *resource;
    int index;

    resource = &scene->resources[0];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], 5), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(2, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);

    resource = &scene->resources[3];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[1], 0), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(2, resource->view.character, 0x1c00, resource->view.character->szByte);

    resource = &scene->resources[4];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], 6), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(0, resource->view.screen, resource->view.character, resource->view.palette, 0x1d, 2);

    resource = &scene->resources[1];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], 0), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(4, resource->view.screen, resource->view.character, resource->view.palette, 0x1f, 0);

    index = 2;
    if (!scene->altLayout) {
        index = 1;
    }
    resource = &scene->resources[2];
    resource->fileData = Archive_LoadFile(ARCHIVE_FILE_ID(scene->archiveFiles[0], index), 0xe);
    GetBgDataFromArchive(&resource->view, resource->fileData, 0, 0, 0);
    DispatchByPartType(7, resource->view.screen, resource->view.character, resource->view.palette, 0x1c, 0);
}
