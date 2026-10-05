extern unsigned int data_ov023_020b6f84;
extern unsigned int GetBgDataFromArchive();
extern unsigned int SetPanelSessionActive();
extern unsigned int func_ov027_020ba1f8();
extern unsigned int func_ov027_020ba200();

void LoadMenuScreenResource(unsigned int resource)

{
  int menu;
  unsigned int handle;
  
  menu = data_ov023_020b6f84;
  handle = func_ov027_020ba1f8(resource);
  *(unsigned int *)(menu + 0x10) = handle;
  GetBgDataFromArchive(menu + 0x14,*(unsigned int *)(menu + 0x10),0,0,0xffffffff);
  func_ov027_020ba200(resource,0);
  *(unsigned int *)(menu + 0x28) = 1;
  SetPanelSessionActive();
  return;
}
