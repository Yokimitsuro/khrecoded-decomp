#include "nitro/types.h"

typedef struct {
    int step;
    u8 pad_04[0x18];
    int frameCount;
    u8 pad_20[0x140];
    u8 records[4];
} PanelIntro;

extern PanelIntro *data_ov015_020812e0;

extern void func_ov002_02062014(int mode);
extern void func_ov002_020664e4(int frames);
extern void func_ov002_020664f4(int frames);
extern BOOL func_ov002_0206655c(void);
extern void func_ov015_02078f58(void);
extern u16 *func_ov002_02062000(void);
extern void UpdateWidgetRootOnly(void *records, u16 id);
extern BOOL func_ov015_020766d0(void);

BOOL RunPanelIntroSequence(void) {
    data_ov015_020812e0->frameCount++;
    switch (data_ov015_020812e0->step) {
    case 0:
        func_ov002_02062014(1);
        data_ov015_020812e0->step = 10;
        break;
    case 10:
        func_ov002_020664e4(3);
        data_ov015_020812e0->step = 20;
        break;
    case 20:
        if (func_ov002_0206655c()) {
            data_ov015_020812e0->step = 100;
        }
        break;
    case 100:
        func_ov015_02078f58();
        UpdateWidgetRootOnly(data_ov015_020812e0->records, *func_ov002_02062000());
        if (!func_ov015_020766d0()) {
            data_ov015_020812e0->step = 200;
        }
        break;
    case 200:
        func_ov002_020664f4(3);
        data_ov015_020812e0->step = 210;
        break;
    case 210:
        if (func_ov002_0206655c()) {
            data_ov015_020812e0->step = 300;
            return FALSE;
        }
        break;
    }
    return TRUE;
}
