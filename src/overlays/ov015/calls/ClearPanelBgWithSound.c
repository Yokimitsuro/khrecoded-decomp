extern unsigned int MI_CpuClear32_0x800();
extern unsigned int G2S_GetBG2ScrPtr();
extern unsigned int PlaySoundEffect();

void ClearPanelBgWithSound(void)

{
  void *dst;
  
  PlaySoundEffect(2,1);
  dst = G2S_GetBG2ScrPtr();
  MI_CpuClear32_0x800(dst);
  return;
}
