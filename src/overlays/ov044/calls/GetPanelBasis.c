#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 axes[3];
} Basis;

extern u32 data_ov044_020d0ec0;

extern void BuildBasisFromForward(const VecFx32 *forward, const VecFx32 *up, Basis *basis);

void GetPanelBasis(Basis *out)
{
    Basis built;
    Basis basis;

    BuildBasisFromForward((VecFx32 *)(data_ov044_020d0ec0 + 0x70), (VecFx32 *)(data_ov044_020d0ec0 + 0x7c), &built);
    basis = built;
    *(Basis *)out = *(Basis *)&basis;
}
