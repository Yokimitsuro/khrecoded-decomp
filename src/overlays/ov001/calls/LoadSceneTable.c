#include "nitro/types.h"

typedef struct SceneEntry {
    u8 pad_00[0x1c];
    u16 *name;
    u32 dataA;
    u32 dataB;
} SceneEntry;

typedef struct SceneTableFile {
    u8 count;
    u8 pad_01[3];
    u16 *title;
    SceneEntry *entries[1];
} SceneTableFile;

typedef struct SceneContext {
    SceneTableFile *table;
    u8 pad_04[4];
    void *archive;
    s8 currentId;
    u8 pad_0d[0x10bc - 0xd];
    u16 *caption;
} SceneContext;

extern SceneContext *data_ov001_020a048c;
extern char sOv001_MiWdWFormat02d_0209eaac[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int mode, int flags);
extern SceneTableFile *Archive_LoadFile(u32 fileId, u32 flags);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern u16 *GetGridTableValue_02051f84(int row, int column);
extern u16 *GetGridTableValue(int row, int column);
extern int Utf16Length(u16 *text);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

void LoadSceneTable(int sceneId)
{
    SceneContext *context = data_ov001_020a048c;
    char path[32];
    int i;
    SceneTableFile *file;
    int slot;
    SceneTableFile *table;
    SceneEntry *entry;
    u16 *text;
    u16 *copy;
    u32 size;

    OS_SPrintf(path, sOv001_MiWdWFormat02d_0209eaac, sceneId + 1);
    context->archive = Msg_OpenContainerAndReadHeader(path, 2, 0);
    file = Archive_LoadFile(0x80000000 | (((u32)context->archive + 0x8000) & 0xfffffc) << 7, 2);
    context->table = file;
    for (i = 0; i < file->count; i++) {
        file->entries[i] = (SceneEntry *)((u8 *)file + (u32)file->entries[i]);
    }
    for (i = 0; i < file->count; i++) {
        entry = file->entries[i];
        entry->dataA += (u32)entry;
        entry->dataB += (u32)entry;
    }
    table = context->table;
    AcquireRecordSlot(0xd, 1);
    for (slot = 0; slot < table->count; slot++) {
        entry = table->entries[slot];
        text = GetGridTableValue_02051f84(sceneId, slot);
        if (text != NULL) {
            size = (Utf16Length(text) + 1) * 2;
            copy = NNSi_FndAllocFromDefaultHeap(size);
            entry->name = copy;
            MIi_CpuCopy16(text, copy, size);
        }
    }
    ReleaseRecordSlot(0xd);
    AcquireRecordSlot(2, 1);
    text = GetGridTableValue(sceneId, -1);
    size = (Utf16Length(text) + 1) * 2;
    copy = NNSi_FndAllocFromDefaultHeap(size);
    table->title = copy;
    MIi_CpuCopy16(text, copy, size);
    text = GetGridTableValue(9, -1);
    size = (Utf16Length(text) + 1) * 2;
    copy = NNSi_FndAllocFromDefaultHeap(size);
    context->caption = copy;
    MIi_CpuCopy16(text, copy, size);
    ReleaseRecordSlot(2);
    context->currentId = sceneId;
}
