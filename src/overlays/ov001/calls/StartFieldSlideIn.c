#include "nitro/types.h"

typedef struct FieldFlags {
    u32 active : 1;
    u32 unk_1 : 3;
    u32 paused : 1;
    u32 reserved : 27;
} FieldFlags;

typedef struct Field {
    u8 pad_000[0x47c];
    s32 state;
    FieldFlags flags;
    u8 pad_484[0x158];
    u8 tween[0x28];
    s32 offset;
} Field;

typedef struct FieldHandle {
    u32 unk_00;
    Field *field;
} FieldHandle;

extern FieldHandle data_ov001_020a04c4;
extern s32 data_0205fde4;

extern BOOL ResumeFieldAfterPause(void *panel);
extern void func_ov001_0207a880(int value);
extern void SetupFieldBgLayers(void);
extern void FlushAndFreeBgScreen(Field *field);
extern void SetFieldMenuSuspended(s32 suspend, s32 checkPanel);
extern void SetMenuHiddenAndReloadChars(int hidden);
extern void func_02052528(void *tween, int mode, int duration, int from, int to);
extern void func_02052570(void *tween);
extern void SetFieldVisiblePlanes(void);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG1OFS (*(vu32 *)0x04000014)
#define REG_WIN0H (*(vu16 *)0x04000040)
#define REG_WIN0V (*(vu16 *)0x04000044)
#define REG_WININ0 (*(vu16 *)0x04000048)
#define REG_WININ1 (*(vu16 *)0x0400004a)

static inline void SetWnd0InsidePlane(int plane, BOOL effect)
{
    u32 value = (REG_WININ0 & ~0x3f) | plane;
    if (effect) {
        value |= 0x20;
    }
    REG_WININ0 = (u16)value;
}

static inline void SetWndOutsidePlane(int plane, BOOL effect)
{
    u32 value = (REG_WININ1 & ~0x3f) | plane;
    if (effect) {
        value |= 0x20;
    }
    REG_WININ1 = (u16)value;
}

static inline void SetVisibleWnd(int mask)
{
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | (mask << 13);
}

BOOL StartFieldSlideIn(void)
{
    Field *field = data_ov001_020a04c4.field;

    if (field->state != 2) {
        return FALSE;
    }
    if (data_0205fde4 != 0) {
        return FALSE;
    }
    if (field->flags.paused == 1) {
        ResumeFieldAfterPause(NULL);
    }
    func_ov001_0207a880(1);
    SetupFieldBgLayers();
    FlushAndFreeBgScreen(field);
    SetFieldMenuSuspended(0, 1);
    SetMenuHiddenAndReloadChars(0);
    func_02052528(field->tween, 2, 0x60000, 0, 100);
    func_02052570(field->tween);
    field->flags.active = 1;
    field->offset = 0x60;
    SetWnd0InsidePlane(1, TRUE);
    SetWndOutsidePlane(0xf, TRUE);
    SetVisibleWnd(1);
    REG_WIN0H = 0xff;
    REG_WIN0V = 0xc0;
    SetFieldVisiblePlanes();
    REG_BG1OFS = 0x280000;
    field->state = 3;
    return TRUE;
}
