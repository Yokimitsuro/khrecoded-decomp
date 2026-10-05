extern unsigned int data_ov031_020bc820;
extern unsigned int ActorRegistry_ForEachCallback();
extern unsigned int func_ov001_020668e4();
extern unsigned int func_ov001_02067d80();
extern unsigned int func_ov001_0206d95c();
extern unsigned int func_ov001_0207ecec();
extern unsigned int StageManager_Update();
extern unsigned int func_ov031_020bac18();
extern unsigned int func_ov031_020bb074();

void ApplyOverlayScaleMode_020bab40(int preserveState)

{
  unsigned int scale;
  
  if ((*(unsigned short *)(data_ov031_020bc820 + 6) & 0x40) != 0) {
    scale = 0x100;
  }
  else {
    scale = 0x1000;
  }
  func_ov031_020bac18();
  func_ov031_020bb074();
  if (preserveState == 0) {
    func_ov001_02067d80(0x1000);
    func_ov001_0207ecec(0x1000);
  }
  func_ov001_0206d95c(scale);
  if (preserveState == 0) {
    StageManager_Update(scale);
    func_ov001_020668e4();
  }
  ActorRegistry_ForEachCallback(0x1000);
  return;
}
