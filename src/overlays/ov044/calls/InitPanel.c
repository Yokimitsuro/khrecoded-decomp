#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad00[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 lookAt;
    u8 pad2c[0x10];
    u32 flags;
    u8 pad40[0x9c];
    VecFx32 savedLookAt;
    VecFx32 savedPosition;
    VecFx32 target;
    VecFx32 origin;
    int fieldOfView;
    int particle;
} Panel;

typedef u32 (*PanelUpdateFunc)(void);

extern Panel *data_ov044_020d0ec0;
extern VecFx32 data_0205344c;

extern void LoadDefaultProjectionValues(unsigned int *projection_values);
extern void EnterPanelState(int state);
extern u32 UpdatePanelState_020d06a0(void);

PanelUpdateFunc InitPanel(int unused, Panel *panel)
{
    VecFx32 defaultTarget;

    data_ov044_020d0ec0 = panel;
    panel->flags = 0;
    LoadDefaultProjectionValues((unsigned int *)panel);
    panel->savedPosition = panel->position;
    panel->savedLookAt = panel->lookAt;
    panel->farClip = 0x6a4000;
    panel->nearClip = 0x19a;
    defaultTarget.x = 0;
    defaultTarget.y = 0;
    defaultTarget.z = -0x2333;
    panel->target = defaultTarget;
    panel->origin = data_0205344c;
    EnterPanelState(0);
    panel->fieldOfView = 0x860;
    panel->particle = 0;
    return UpdatePanelState_020d06a0;
}
