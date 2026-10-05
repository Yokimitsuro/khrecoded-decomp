extern unsigned int data_ov015_0207e960;
extern unsigned int PlaySoundEffect();

void UpdatePanelSelectionSound(int context)

{
  int previousSelection;
  
  previousSelection = *(int *)(data_ov015_0207e960 + 200);
  *(unsigned int *)(data_ov015_0207e960 + 200) = *(unsigned int *)(context + 0xc);
  if (*(int *)(data_ov015_0207e960 + 200) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
