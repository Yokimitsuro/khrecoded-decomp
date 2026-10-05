#include "nitro/types.h"

typedef struct {
    u32 state;
    u8 selection;
    u8 pad_05[3];
    u8 *record;
    u8 pad_0c[0x48];
    u32 field_54;
    u32 field_58;
    u32 field_5c;
} UnitResources;

extern const char *gSoundCategoryNames[];
extern const char sOv021_BaChFormatSCpBZ_020b5258[];
extern const char data_ov021_020b5268[];
extern void *GetOverlaySelectionRecord(u32 selectionIndex);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(const char *path, u32 flags);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void func_ov021_020a9d88(UnitResources *unit, void *data, int kind);
extern void func_ov021_020a9eec(UnitResources *unit, void *arg, int kind, void *data);

void InitUnitResources(UnitResources *unit, void *arg, int kind, u32 selection)
{
    void *data;
    void *file;
    char motionPath[0x81];
    char modelPath[0x7f];

    unit->state = 0;
    unit->field_54 = 0;
    unit->field_5c = 0;
    unit->field_58 = 0;
    unit->selection = selection;
    unit->record = (u8 *)GetOverlaySelectionRecord(selection) + 0x10;
    OS_SPrintf(motionPath, sOv021_BaChFormatSCpBZ_020b5258, gSoundCategoryNames[kind]);
    data = func_0202c4a0(motionPath, 0x11);
    func_ov021_020a9d88(unit, data, kind);
    NNSi_FndFreeFromDefaultHeap(data);
    OS_SPrintf(modelPath, data_ov021_020b5268, gSoundCategoryNames[kind]);
    file = func_0202c4a0(modelPath, 0x11);
    func_ov021_020a9eec(unit, arg, kind, file);
    NNSi_FndFreeFromDefaultHeap(file);
}
