#include "nitro/types.h"

typedef struct {
    u8 pad0[0x134];
    int group;
    int pad138;
    int subPage;
    u8 pad140[0x10];
    int touchMode;
    int sliderActive;
    u8 pad158[0x1c];
    u8 tileTable[0x6c];
    u8 sourceBlock[8];
} RecordPanel;

extern u8 *data_0205fe0c;
extern BOOL func_ov039_020bc10c(void);
extern void *func_ov039_020bc1dc(void);
extern void *func_ov039_020bc1ec(void);
extern void SetWidgetRootDpadEnabled(void *root, BOOL enabled);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern s64 OS_GetTick(void);
extern s64 GetCardThreadStartTick(void);
extern int func_ov027_020b9f9c(void *dst);
extern void ClearScreenLayerDirty(int layerId);
extern void func_ov027_020b9e80(void *table);
extern void SetPageHeaderVisible(RecordPanel *panel, int mode);
extern void UpdateRecordSliderTouch(RecordPanel *panel);
extern BOOL func_ov086_020c1694(RecordPanel *panel, int mode);
extern void HandleRecordScrollInput(RecordPanel *panel);
extern void DrawPlayTimeDigits(RecordPanel *panel, int seconds);

void UpdateRecordPanelInput(RecordPanel *panel)
{
    int group;
    u64 playSeconds;

    if (panel->touchMode) {
        if (!func_ov039_020bc10c()) {
            panel->touchMode = 0;
            SetPageHeaderVisible(panel, 0);
        } else if (panel->sliderActive) {
            UpdateRecordSliderTouch(panel);
        } else if (!func_ov086_020c1694(panel, 0)) {
            group = panel->group;
            if (group != 7) {
                if ((group == 6 && panel->subPage == 1) || (group != 6 && panel->subPage != 0)) {
                    HandleRecordScrollInput(panel);
                }
            }
        }
    } else if (func_ov039_020bc10c() || func_ov086_020c1694(panel, 1)) {
        panel->touchMode = 1;
        SetPageHeaderVisible(panel, 1);
        SetWidgetRootDpadEnabled(func_ov039_020bc1dc(), 0);
        SetWidgetRootDpadEnabled(func_ov039_020bc1ec(), 1);
        SetPrimaryElementEnabled(0);
        SetSecondaryElementEnabled(1);
    }
    playSeconds = *(u32 *)(data_0205fe0c + 0x28c8) + (u64)(OS_GetTick() - GetCardThreadStartTick()) * 64 / 0x1ff6210;
    DrawPlayTimeDigits(panel, playSeconds);
    func_ov027_020b9f9c(panel->sourceBlock);
    ClearScreenLayerDirty(0x19);
    ClearScreenLayerDirty(0x1a);
    func_ov027_020b9e80(panel->tileTable);
}
