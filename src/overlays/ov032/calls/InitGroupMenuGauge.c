#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *pixels;
} CharacterData;

typedef struct {
    u8 *gaugeSource;
    u8 *gaugeTiles;
    void *mainCharFile;
    void *subCharFile;
    CharacterData *mainChar;
    CharacterData *subChar;
    u8 pad_18[0x10];
    BOOL snap;
} GaugeMenu;

typedef u32 (*MenuStateFunc)(void);

extern struct {
    int reserved;
    GaugeMenu *menu;
} data_ov032_020c0088;

extern void *GetSceneTagTracker(void);
extern GaugeMenu *NNSi_FndGetCurrentRootHeap(void);
extern unsigned int MakePrimaryVramKey(unsigned int slot);
extern unsigned int MakePrimaryVramKey_02071214(unsigned int slot);
extern void *func_0202c4a0(unsigned int key, u32 heapId);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *file, CharacterData **out);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void UploadGroupMenuTiles(int arg);
extern void SetGroupMenuProgress(int percent);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b824c(void *pool, void *record, int arg2, int arg3);
extern u32 UpdateGroupMenuCounter(void);

MenuStateFunc InitGroupMenuGauge(void)
{
    GaugeMenu *menu;
    void *file;
    CharacterData *charData;
    void *tracker;

    GetSceneTagTracker();
    menu = NNSi_FndGetCurrentRootHeap();
    data_ov032_020c0088.menu = menu;
    menu->snap = TRUE;
    file = func_0202c4a0(MakePrimaryVramKey(7), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(file, &charData);
    menu->gaugeSource = NNSi_FndAllocFromDefaultHeap(0x160);
    menu->gaugeTiles = NNSi_FndAllocFromDefaultHeap(0x160);
    MIi_CpuCopyFast(charData->pixels, menu->gaugeSource, 0x160);
    NNSi_FndFreeFromDefaultHeap(file);
    menu->mainCharFile = func_0202c4a0(MakePrimaryVramKey_02071214(3), 0xe);
    menu->subCharFile = func_0202c4a0(MakePrimaryVramKey_02071214(4), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(menu->mainCharFile, &menu->mainChar);
    NNS_G2dGetUnpackedBGCharacterData(menu->subCharFile, &menu->subChar);
    UploadGroupMenuTiles(0);
    SetGroupMenuProgress(0);
    tracker = GetSceneTagTracker();
    func_ov027_020b824c(tracker, FindActiveRecordById(tracker, 5), -2, 1);
    return UpdateGroupMenuCounter;
}
