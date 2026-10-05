#include "nitro/types.h"

#define reg_GX_DISPCNT (*(REGType32v *)0x04000000)

typedef struct PanelResource {
    u8 pad_00[0x14];
    void *charData;
} PanelResource;

typedef struct PanelFlags {
    u32 visible : 1;
    u32 active : 1;
    u32 closing : 1;
} PanelFlags;

typedef struct PanelRect {
    s16 x;
    s16 y;
    u16 width;
    u16 height;
} PanelRect;

typedef struct MenuPanel {
    s32 state;
    s32 owner;
    u8 pad_0008[0x9c08 - 8];
    PanelResource *resource;
    PanelRect rect;
    u8 sprite[0x9c30 - 0x9c14];
    s32 userArg;
    s32 messageArg;
    PanelFlags flags;
} MenuPanel;

extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void func_02052570(void *record);
extern void *G2_GetBG1CharPtr(void);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void SetSecondaryElementEnabled(BOOL enabled);

static inline int GetVisiblePlane(void)
{
    return (int)((reg_GX_DISPCNT & 0x1f00) >> 8);
}

static inline void SetVisiblePlane(int plane)
{
    reg_GX_DISPCNT = (u32)((reg_GX_DISPCNT & ~0x1f00) | (plane << 8));
}

static inline void SetRect(PanelRect *rect, int x, int y, u16 width, u16 height)
{
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
}

void MenuPanel_Setup(MenuPanel *panel, int owner, int x, int y, u16 width, u16 height, int priority, int userArg, int messageArg)
{
    panel->state = 0;
    panel->owner = owner;
    SetRect(&panel->rect, x + (0x20 - width) / 2, y, width, height);
    panel->userArg = userArg;
    panel->messageArg = messageArg;
    panel->flags.visible = 0;
    panel->flags.active = 0;
    panel->flags.closing = 0;
    func_02052528(panel->sprite, 0, 0, 0x1000, priority);
    func_02052570(panel->sprite);
    MIi_CpuCopyFast(panel->resource->charData, G2_GetBG1CharPtr(), 0x140);
    SetSecondaryElementEnabled(FALSE);
    SetVisiblePlane(GetVisiblePlane() | 2);
}
