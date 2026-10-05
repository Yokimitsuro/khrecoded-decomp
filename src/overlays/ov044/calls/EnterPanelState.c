#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
} PanelPath;

typedef struct {
    u8 pad00[0x40];
    int prevState;
    int state;
    u8 pad48[4];
    PanelPath path;
    u8 pad64[0xc];
    VecFx32 forward;
    VecFx32 up;
    u8 pad88[0x48];
    VecFx32 stateTarget;
    u8 paddc[0x18];
    VecFx32 target;
} Panel;

extern Panel *data_ov044_020d0ec0;
extern PanelPath data_ov044_020d0e10[];

extern void func_ov044_020d0748(const VecFx32 *path, VecFx32 *out, VecFx32 *out2);

void EnterPanelState(int state)
{
    data_ov044_020d0ec0->prevState = state;
    data_ov044_020d0ec0->state = state;
    data_ov044_020d0ec0->path = data_ov044_020d0e10[state];
    func_ov044_020d0748(&data_ov044_020d0ec0->path.end, &data_ov044_020d0ec0->forward, &data_ov044_020d0ec0->up);
    if (data_ov044_020d0ec0->state == 6) {
        data_ov044_020d0ec0->target = data_ov044_020d0ec0->stateTarget;
    } else if (data_ov044_020d0ec0->prevState == 6) {
        VecFx32 defaultTarget;

        defaultTarget.x = 0;
        defaultTarget.y = 0;
        defaultTarget.z = -0x2333;

        data_ov044_020d0ec0->target = defaultTarget;
    }
}

