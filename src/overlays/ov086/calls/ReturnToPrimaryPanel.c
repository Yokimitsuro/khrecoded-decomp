#include "nitro/types.h"

extern u8 *func_ov039_020bc1dc(void);
extern void SetWidgetRootDpadEnabled(u8 *panel, BOOL enable);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ReturnToPrimaryPanel(void)
{
    SetWidgetRootDpadEnabled(func_ov039_020bc1dc(), TRUE);
    SetPrimaryElementEnabled(TRUE);
    SetSecondaryElementEnabled(FALSE);
    PlaySoundEffect(0, 3);
}
