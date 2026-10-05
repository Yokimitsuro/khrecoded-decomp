extern unsigned int data_ov023_020b6f0c;
extern unsigned int GXS_LoadOBJPltt();

void SelectMenuPalette(int menu,int palette)

{
  if ((1 <= palette) && (palette <= 4)) {
    GXS_LoadOBJPltt((unsigned char *)&data_ov023_020b6f0c + (palette + -1) * 8,2,8);
    *(int *)(menu + 0x6870) = palette;
  }
  return;
}
