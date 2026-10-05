#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x14];
    void *buffer;
    u8 slotCount;
    u8 pad_019[0x7];
    u32 unk_20;
    u8 pad_024[0x514];
    u32 heapHandle;
    u8 pad_53c[0x1dd8];
    void *table;
} Scene;

typedef struct {
    s16 kind;
} PlayerFlagRecord;

extern void func_ov041_020bdf20(void);
extern void func_ov041_020bdc28(void);
extern void func_ov041_020c0acc(int slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(u32 value);
extern void func_ov041_020be224(void);
extern void PXI_Init_0202a64c(u32 value);
extern void func_ov041_020ce200(void *object);
extern void func_ov041_020be090(void);
extern PlayerFlagRecord *GetPlayerFlagRecord(int index);
extern void SetMenuEntryHighlight(int menu, int index, int highlighted);
extern u8 *GetOverlaySelectionRecord(int index);
extern void func_ov001_0207d680(void);
extern void PopVramState(void);

void ShutdownMenuScene(Scene **scenePtr) {
    int i;
    Scene *scene = *scenePtr;

    func_ov041_020bdf20();
    func_ov041_020bdc28();
    for (i = 0; i < scene->slotCount; i++) {
        func_ov041_020c0acc((u8)i);
    }
    if (scene->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene->buffer);
        scene->buffer = NULL;
    }
    ZeroHalfThenFree(scene->heapHandle);
    NNSi_FndFreeFromDefaultHeap(scene->table);
    func_ov041_020be224();
    PXI_Init_0202a64c(scene->unk_20);
    func_ov041_020ce200((u8 *)scene + 0x53c);
    if (scene != NULL) {
        NNSi_FndFreeFromDefaultHeap(scene);
        *scenePtr = NULL;
    }
    func_ov041_020be090();
    for (i = 0; i < 8; i++) {
        if (GetPlayerFlagRecord(i) != NULL) {
            switch (GetPlayerFlagRecord(i)->kind) {
            case 0xd0:
            case 0xd1:
            case 0xd2:
                SetMenuEntryHighlight(1, i, 1);
                break;
            default:
                SetMenuEntryHighlight(1, i, 0);
                break;
            }
        }
    }
    for (i = 0; i < *(int *)(GetOverlaySelectionRecord(0) + 300); i++) {
        GetOverlaySelectionRecord(0);
        SetMenuEntryHighlight(0, i, 0);
    }
    func_ov001_0207d680();
    PopVramState();
}
