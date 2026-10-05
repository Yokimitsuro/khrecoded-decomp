#include "nitro/types.h"

typedef struct {
    void **objects;
    s8 count;
    u8 pad_05[7];
    u8 *resource;
    void *buffer;
    u8 pad_14[0x110];
} FieldObjectManager;

extern FieldObjectManager *data_ov001_020a04f8;
extern char sOv001_MoMo_0209f038[];
extern char gFieldObjectScriptCommandHandlers[];
extern void StoreGlobalArrayEntry(int index, void *value);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern u8 *Msg_OpenContainerAndReadHeader(const char *path, int mode, int flags);
extern void func_ov001_02063560(int slot, u8 *resource);
extern void *Archive_LoadFile(u32 fileId, u32 flags);
extern void func_ov001_02086c38(void);

void CreateFieldObjectManager(void)
{
    StoreGlobalArrayEntry(4, gFieldObjectScriptCommandHandlers);
    data_ov001_020a04f8 = NNSi_FndAllocFromDefaultHeap(sizeof(FieldObjectManager));
    MIi_CpuClearFast(0, data_ov001_020a04f8, sizeof(FieldObjectManager));
    data_ov001_020a04f8->resource = Msg_OpenContainerAndReadHeader(sOv001_MoMo_0209f038, 3, 0);
    func_ov001_02063560(1, data_ov001_020a04f8->resource);
    data_ov001_020a04f8->buffer = Archive_LoadFile(0x80000000 | (((u32)data_ov001_020a04f8->resource + 0x8000) & 0xfffffc) << 7, 3);
    func_ov001_02086c38();
}
