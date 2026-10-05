extern unsigned int NNS_G2dBGLoadScreenRect();
extern unsigned int GetWidgetTileDimensions();

void CopyWidgetScreenRegion(int screen,int widget,void *destination)

{
  int width;
  int height;
  
  if (destination != (void *)0x0) {
    GetWidgetTileDimensions(widget,&width,&height);
    NNS_G2dBGLoadScreenRect
              (destination,*(void **)(*(int *)(widget + 0x18) + 8),(unsigned int)*(unsigned short *)(widget + 6),
               (unsigned int)*(unsigned short *)(widget + 8),(int)*(short *)(widget + 2),
               (int)*(short *)(widget + 4),(unsigned int)*(unsigned short *)(screen + 8),
               (unsigned int)*(unsigned short *)(screen + 10),width,height);
    return;
  }
  return;
}
