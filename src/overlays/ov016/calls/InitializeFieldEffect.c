extern unsigned int SpawnSoundSlot();
extern unsigned int func_ov016_020a298c();
extern unsigned int StartFieldUnitMotion();
extern unsigned int func_ov016_020a2c2c();

void InitializeFieldEffect(int object,unsigned int selection)

{
  unsigned int effect;
  
  *(unsigned int *)(object + 0xd8) = *(unsigned int *)(object + 0xd8) & 0xffffff00 | selection & 0xff;
  *(unsigned int *)(object + 0xcc) = 0;
  effect = StartFieldUnitMotion(object,0x2400,0);
  *(unsigned int *)(object + 0xd0) = effect;
  func_ov016_020a2c2c(object);
  func_ov016_020a298c(object,selection != 0xff);
  *(unsigned char *)(object + 0xbe) = *(unsigned char *)(object + 0xbe) & ~0xf0 | 0x40;
  SpawnSoundSlot(0,0x3d,object + 0x38,0);
  return;
}
