extern unsigned int data_ov028_020bb3a0;
extern unsigned int StartIdleSceneObjects();
extern unsigned int func_ov001_02087650();

unsigned int EnterOverlayTransition(void)

{
  unsigned short flags;
  
  flags = *(unsigned short *)(data_ov028_020bb3a0 + 6);
  flags |= 0x20;
  *(unsigned short *)(data_ov028_020bb3a0 + 6) = flags;
  if ((flags & 0x10) == 0) {
    StartIdleSceneObjects();
    func_ov001_02087650(1);
  }
  return 0xf;
}
