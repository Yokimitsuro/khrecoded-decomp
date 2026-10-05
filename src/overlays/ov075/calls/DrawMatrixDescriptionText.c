extern unsigned int CallVirtualHandlerSlot1();
extern unsigned int DrawTextColored();
extern unsigned int Text_UploadTileBuffer();

void DrawMatrixDescriptionText(int context)

{
  CallVirtualHandlerSlot1((void *)(context + 0x11f44),0);
  if (*(void **)(context + 0x11fac) != (void *)0x0) {
    DrawTextColored
              ((void *)(context + 0x11f44),2,4,2,10,*(void **)(context + 0x11fac));
  }
  Text_UploadTileBuffer((void *)(context + 0x11f44));
  return;
}
