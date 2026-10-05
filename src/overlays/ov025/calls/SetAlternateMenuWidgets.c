#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 FindWidgetById();
extern u32 SetEntrySlotsVisible();

void SetAlternateMenuWidgets(int enabled)

{
  int menu;
  u32 widget;
  
  menu = data_ov025_020b7780;
  *(u8 *)(data_ov025_020b7780 + 0x64e9) = enabled != 0;
  if (enabled != 0) {
    widget = FindWidgetById(menu + 0x4c,0x15);
    SetEntrySlotsVisible(menu + 0x4c,widget,1);
    widget = FindWidgetById(menu + 0x4c,3);
    SetEntrySlotsVisible(menu + 0x4c,widget,0);
    return;
  }
  widget = FindWidgetById(menu + 0x4c,0x15);
  SetEntrySlotsVisible(menu + 0x4c,widget,0);
  widget = FindWidgetById(menu + 0x4c,3);
  SetEntrySlotsVisible(menu + 0x4c,widget,1);
  return;
}
