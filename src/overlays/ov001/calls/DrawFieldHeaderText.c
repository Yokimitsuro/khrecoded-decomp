#include "nitro/types.h"

typedef struct HeaderGraphic {
    u8 pad_00[0x24];
    int vramOffset;
} HeaderGraphic;

typedef struct FieldHeader {
    u8 pad_00[0x34];
    void *textLayer;
    u8 pad_38[0x1c];
    HeaderGraphic *graphic;
} FieldHeader;

typedef struct FieldManager {
    u8 pad_000[0x550];
    FieldHeader header;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern void CallVirtualHandlerSlot1(void **context, int arg);
extern void DrawTextAnchored(void **layer, int x, int y, int color, u32 flags, const u16 *text);
extern BOOL func_ov001_0207b3f4(void);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int value, int address, int size);

void DrawFieldHeaderText(const u16 *text)
{
    FieldHeader *header = &data_ov001_020a04c4.manager->header;

    CallVirtualHandlerSlot1(&header->textLayer, 1);
    DrawTextAnchored(&header->textLayer, 4, 3, 2, 0x209, text);
    if (!func_ov001_0207b3f4()) {
        NNS_GfdRegisterNewVramTransferTask(0x15, 0x1000, header->graphic->vramOffset, 0x780);
    }
}
