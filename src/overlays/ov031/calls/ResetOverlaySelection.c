extern unsigned int data_ov031_020bc820;
extern unsigned int func_ov001_0207b4c4();
extern unsigned int AdvanceRecordStep();

void ResetOverlaySelection(void)

{
  unsigned int enabledScale;
  
  *(unsigned int *)(data_ov031_020bc820 + 0x40) = 0xffffffff;
  AdvanceRecordStep();
  if (*(unsigned char *)(data_ov031_020bc820 + 0x54) == '\x01') {
    enabledScale = 0x1000;
  }
  else {
    enabledScale = 0;
  }
  func_ov001_0207b4c4(0,0x1000,enabledScale);
  return;
}
