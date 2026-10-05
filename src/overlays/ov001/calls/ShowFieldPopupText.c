#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u8 *tiles;
} FontData;

typedef struct {
    int active;
    u8 timer[0x1c];
    u64 duration;
    u8 pad_28[0xc];
    u8 layer[0x20];
    FontData *font;
    u8 pad_58[0x10];
    u16 *text;
    u16 *cursor;
    u8 *tileBuffer;
    int mode;
    int pad_78;
    int pending;
} FieldPopup;

typedef struct {
    u8 pad_000[0x47c];
    int busy;
    u32 pad_bits0 : 17;
    u32 locked : 1;
    u32 pad_bits1 : 14;
    u8 pad_484[0x88];
    int captionObject[0x11];
    FieldPopup popup;
} FieldManager;

typedef struct {
    u32 pad_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct {
    u8 pad_000[0x214];
    u32 pad_bits0 : 11;
    u32 popupDisabled : 1;
    u32 pad_bits1 : 20;
} Session;

extern FieldManagerHandle data_ov001_020a04c4;
extern Session *data_ov001_020a0480;
extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern int Utf16Length(u16 *text);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void CallVirtualHandlerSlot1(void *layer, int arg);
extern void Text_UploadTileBuffer(void *layer);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void *func_ov027_020ba2c8(int *object, int index);
extern void SetFieldCaptionText(int captionId);

BOOL ShowFieldPopupText(u16 *text, u32 frames)
{
    FieldPopup *popup;
    FieldManager *manager;
    u8 *tiles;
    u32 size;

    manager = data_ov001_020a04c4.manager;
    popup = &manager->popup;

    if (manager->busy != 0) {
        return FALSE;
    }
    if (popup->active != 0) {
        return FALSE;
    }
    popup->pending = 1;
    popup->duration = (u64)((s64)frames * 0x82ea) >> 6;
    func_02052528(popup->timer, 4, 0x28000, 0, 500);
    if (popup->text != NULL) {
        NNSi_FndFreeFromDefaultHeap(popup->text);
    }
    size = (Utf16Length(text) + 1) * 2;
    popup->text = NNS_FndAllocFromDefaultExpHeapEx(size, -4);
    popup->cursor = popup->text;
    MIi_CpuCopy16(text, popup->text, size);
    popup->mode = 4;
    CallVirtualHandlerSlot1(popup->layer, 1);
    tiles = popup->font->tiles;
    MIi_CpuCopyFast(popup->tileBuffer, tiles, 0x20);
    MIi_CpuCopyFast(popup->tileBuffer + 0x20, tiles + 0x3a0, 0x20);
    MIi_CpuCopyFast(popup->tileBuffer + 0x40, tiles + 0x760, 0x20);
    Text_UploadTileBuffer(popup->layer);
    if (!data_ov001_020a0480->popupDisabled && ReadSessionPackedBits(0x1a00, 2) == 1) {
        SetFieldCaptionText((int)func_ov027_020ba2c8(manager->captionObject, 2));
        manager->locked = 1;
    }
    return TRUE;
}
