#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int size;
    int source;
} TileResource;

typedef struct {
    u8 pad_00[0x10];
    TileResource *alternate;
    TileResource *normal;
} MenuResources;

extern struct { int reserved; MenuResources *menu; } data_ov032_020c0088;
extern void UploadGroupPaletteSegment(int alternate);
extern int NNS_GfdRegisterNewVramTransferTask(void *a, int b, int c, int d);

void UploadGroupMenuTiles(int alternate)
{
    MenuResources *menu = data_ov032_020c0088.menu;
    TileResource *resource;
    if (alternate == 0) {
        resource = menu->normal;
        UploadGroupPaletteSegment(FALSE);
    } else {
        resource = menu->alternate;
        UploadGroupPaletteSegment(TRUE);
    }
    NNS_GfdRegisterNewVramTransferTask((void *)7, 0x5000, resource->source, resource->size);
}
