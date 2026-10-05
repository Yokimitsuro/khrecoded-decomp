#include "nitro/types.h"

typedef struct Ov038ImageResource {
    u8 pad_00[0x10];
    u32 size;
} Ov038ImageResource;

typedef struct Ov038ResourceView {
    u16 *header;
    Ov038ImageResource *image;
    void *extra;
} Ov038ResourceView;

typedef struct Ov038ResourceSlot {
    void *file;
    Ov038ResourceView view;
} Ov038ResourceSlot;

typedef struct Ov038Context {
    u32 unk_00;
    u32 sourceBuffers[3];
    Ov038ResourceSlot slots[3];
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern void GetBgDataFromArchive(Ov038ResourceView *view, void *file, int first, int second, int flags);
extern void DispatchByPartType(int bgIndex, u16 *header, Ov038ImageResource *image, void *extra,
                                        int mask, int flags);
extern int Gfx_EnqueueTableCmdAt14(int tableIndex, Ov038ImageResource *image, int offset, u32 size);

void LoadOv038Graphics(void)
{
    Ov038Context *context = data_ov038_020bd164;

    context->slots[0].file = Archive_LoadFile(((context->sourceBuffers[0] + 0x8000) & 0xfffffc) << 7 | 0x80000002, 0xe);
    GetBgDataFromArchive(&context->slots[0].view, context->slots[0].file, 0, 0, 0);
    DispatchByPartType(0, context->slots[0].view.header, context->slots[0].view.image,
                                context->slots[0].view.extra, 0x1f, 0);

    context->slots[1].file = Archive_LoadFile(((context->sourceBuffers[0] + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive(&context->slots[1].view, context->slots[1].file, 0, 0, 0);
    DispatchByPartType(4, context->slots[1].view.header, context->slots[1].view.image,
                                context->slots[1].view.extra, 0x1f, 0);

    context->slots[2].file = Archive_LoadFile(((context->sourceBuffers[1] + 0x8000) & 0xfffffc) << 7 | 0x80000000, 0xe);
    GetBgDataFromArchive(&context->slots[2].view, context->slots[2].file, 0, 0, 0);
    Gfx_EnqueueTableCmdAt14(4, context->slots[2].view.image, 0, context->slots[2].view.image->size);
}
