#include "nitro/types.h"

typedef struct MenuPanel MenuPanel;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov076_020c9c7c(MenuPanel *panel, BOOL confirmed);

int MenuPanel_Close(MenuPanel *panel)
{
    PlaySoundEffect(1, 3);
    func_ov076_020c9c7c(panel, TRUE);
    return 3;
}
