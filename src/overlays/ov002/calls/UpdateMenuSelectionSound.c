extern unsigned int data_ov002_0206c464;
extern unsigned int PlaySoundEffect();

void UpdateMenuSelectionSound(int context)

{
  int previousSelection;
  
  previousSelection = *(int *)(data_ov002_0206c464 + 0xc);
  *(unsigned int *)(data_ov002_0206c464 + 0xc) = *(unsigned int *)(context + 0xc);
  if (*(int *)(data_ov002_0206c464 + 0xc) == previousSelection) {
    return;
  }
  PlaySoundEffect(2,0);
  return;
}
