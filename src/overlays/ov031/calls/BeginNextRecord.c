#include "nitro/types.h"

typedef struct {
    s32 target;
    s32 from;
    s32 to;
} RecordCue;

typedef struct {
    u8 pad_00[0x14];
    u32 position;
    RecordCue cue;
    s32 layoutStep;
    u8 pad_28[0x14];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x28];
    u32 position;
    u8 pad_2c[0xc];
    u32 unk_38;
    u8 pad_3c[0x8];
    s32 recordIndex;
    s32 nextRecordIndex;
    u8 pad_4c[0x4];
    ActiveRecord *records;
    u8 pad_54[0x5c];
    u32 layoutCounter;
    u8 pad_b4[0xc];
    u32 cueFlag;
    s32 cueFrom;
    s32 cueTo;
    s32 directCue;
    s32 cueTarget;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void func_ov031_020bb710(void);
extern void UpdateRecordActors(void);
extern void RestoreActiveRecordItems(void);
extern void PlaceRecordPanels(void);
extern s32 func_ov001_02063a4c(void);
extern void SetFields30And34(u32 a, u32 b);
extern void ResetCameraUp(s32 angle);
extern void StartSlotLayoutAnimation(int slot, u16 step);
extern void func_ov001_0207d468(int value);

static inline void ApplyRecordCue(RecordCue *cue)
{
    if (cue->target != 0x7fffffff) {
        if (cue->from != 0x7fffffff && cue->from != 0) {
            data_ov031_020bc820->cueFlag = 0;
            data_ov031_020bc820->cueFrom = cue->from;
            data_ov031_020bc820->cueTo = cue->to;
            data_ov031_020bc820->cueTarget = cue->target;
        } else {
            ResetCameraUp(cue->target);
            data_ov031_020bc820->directCue = cue->target;
        }
    }
}

void BeginNextRecord(void)
{
    ActiveRecord *record;

    data_ov031_020bc820->recordIndex = data_ov031_020bc820->nextRecordIndex;
    data_ov031_020bc820->nextRecordIndex = -1;
    data_ov031_020bc820->unk_38 = 0;
    func_ov031_020bb710();
    UpdateRecordActors();
    RestoreActiveRecordItems();
    PlaceRecordPanels();
    record = &data_ov031_020bc820->records[data_ov031_020bc820->recordIndex];
    if (func_ov001_02063a4c() == 4) {
        if (data_ov031_020bc820->position != record->position) {
            SetFields30And34(record->position, 0x52);
        }
        ApplyRecordCue(&record->cue);
    }
    if (record->layoutStep != 0) {
        data_ov031_020bc820->layoutCounter++;
        StartSlotLayoutAnimation(3, data_ov031_020bc820->layoutCounter);
        func_ov001_0207d468(1);
    }
}
