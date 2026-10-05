#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov032_020c0088;
#define activeMenu data_ov032_020c0088.context
extern u32 IsFieldPanelHidden();
extern u32 func_ov032_020bb914();
extern u32 func_ov032_020bba00();

u32 UpdateGroupMenuCounter(void)

{
  int menu;
  int ready;
  
  menu = activeMenu;
  if (*(int *)(activeMenu + 0x18) == 100) {
    func_ov032_020bb914(activeMenu);
  }
  if ((*(int *)(menu + 0x20) != *(int *)(menu + 0x24)) &&
     (ready = IsFieldPanelHidden(), ready != 0)) {
    func_ov032_020bba00(menu);
  }
  return 0;
}
