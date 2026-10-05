#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    s32 param;
    s32 itemId;
} PanelSpawn;

typedef struct {
    u8 pad_00[0x8];
    VecFx32 origin;
    u8 pad_14[0x20];
    PanelSpawn *panelSpawns;
    u8 pad_38[0x3];
    u8 panelCount;
} ActiveRecord;

typedef struct {
    u8 pad_00[0x44];
    s32 recordIndex;
    u8 pad_48[0x8];
    ActiveRecord *records;
} OverlayState;

typedef struct {
    u8 pad_00[0x7d];
    u8 type;
} PanelInfo;

typedef struct {
    u8 pad_00[0x8];
    PanelInfo *info;
    u8 pad_0c[0x42];
    u16 flags;
} Panel;

typedef struct {
    u8 pad_00[0x46];
    u16 panelCount;
} PanelLayer;

extern OverlayState *data_ov031_020bc820;
extern void *func_ov001_02087264(void);
extern int func_ov001_0207f040(void);
extern PanelLayer *func_ov001_0207f050(int index);
extern Panel *func_ov001_0207f060(int layer, int index);
extern BOOL func_ov001_02082730(Panel *panel);
extern s8 func_ov001_02068084(void);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void InitItemPanel(Panel *panel, const VecFx32 *position, int itemId, int param);

static inline u8 GetPanelType(int layerIndex, int panelIndex)
{
    return func_ov001_0207f060(layerIndex, panelIndex)->info->type;
}

void PlaceRecordPanels(void)
{
    ActiveRecord *record;
    u32 placed;
    int layerCount;
    int i;
    int j;
    PanelLayer *layer;
    int count;
    Panel *panel;
    VecFx32 position;

    record = &data_ov031_020bc820->records[data_ov031_020bc820->recordIndex];
    if (record->panelCount == 0 || func_ov001_02087264() == NULL) {
        return;
    }
    placed = 0;
    layerCount = func_ov001_0207f040();
    for (i = 0; i < layerCount; i++) {
        j = 0;
        layer = func_ov001_0207f050(i);
        if (layer != NULL && layer->panelCount != 0 && GetPanelType(i, j) == 11) {
            count = layer->panelCount;
            for (; j < count; j++) {
                panel = func_ov001_0207f060(i, j);
                if ((panel->flags & 4) && !func_ov001_02082730(panel)) {
                    position = record->panelSpawns[placed].position;
                    if (func_ov001_02068084() != 6) {
                        ScaleVecFx32InPlace(&position, 0xaab);
                    }
                    VEC_Subtract(&position, &record->origin, &position);
                    InitItemPanel(panel, &position, record->panelSpawns[placed].itemId,
                                           record->panelSpawns[placed].param);
                    placed++;
                    if (placed == record->panelCount) {
                        return;
                    }
                }
            }
            break;
        }
    }
}


