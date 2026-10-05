extern unsigned int data_ov025_020b7780;
extern unsigned int func_ov025_020b584c();
extern unsigned int func_ov025_020b5928();
extern unsigned int func_ov027_020ba1f8();
extern unsigned int func_ov027_020ba200();

void LoadMenuWidgetResource(unsigned int resource)

{
  unsigned int menu;
  unsigned int handle;
  
  menu = data_ov025_020b7780;
  handle = func_ov027_020ba1f8(resource);
  func_ov025_020b5928(menu,handle);
  func_ov027_020ba200(resource,1);
  func_ov025_020b584c(menu);
  return;
}
