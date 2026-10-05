#include "nitro/types.h"

typedef struct PackedFileHeader {
    u32 payloadOffset;
    u32 count;
} PackedFileHeader;

typedef struct PackedFileView {
    PackedFileHeader *file;
    u32 count;
    u8 *payload;
} PackedFileView;

extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern PackedFileHeader *Archive_LoadFile(u32 fileId, u32 heapId);
extern PackedFileHeader *func_0202c4a0(u32 fileId, u32 heapId);

void LoadPackedFileView(PackedFileView *view, u32 fileId, BOOL fromTail)
{
    PackedFileHeader *file;
    u32 offset;

    MI_CpuFill8(view, 0, sizeof(PackedFileView));
    if (fromTail) {
        view->file = func_0202c4a0(fileId, 14);
    } else {
        view->file = Archive_LoadFile(fileId, 14);
    }
    file = view->file;
    offset = file->payloadOffset;
    view->count = file->count;
    view->payload = (u8 *)file + offset;
}
