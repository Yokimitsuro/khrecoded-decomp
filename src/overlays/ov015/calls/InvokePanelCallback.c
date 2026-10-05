#include "nitro/types.h"

typedef void PanelCallback(void *context);
extern u32 data_ov015_0207e964;

void InvokePanelCallback(void *context)

{
  if (*(PanelCallback **)(data_ov015_0207e964 + 0x90) == (PanelCallback *)0x0) {
    return;
  }
  (**(PanelCallback **)(data_ov015_0207e964 + 0x90))(context);
  return;
}
