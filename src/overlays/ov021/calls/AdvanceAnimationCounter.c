extern unsigned int AdvanceOwnerAnimation();

unsigned int AdvanceAnimationCounter(unsigned int context,int animation,int step)

{
  int descriptor;
  int counter;
  
  descriptor = *(int *)(animation + 0x138);
  AdvanceOwnerAnimation(animation,step);
  counter = *(int *)(animation + 4) + step;
  *(int *)(animation + 4) = counter;
  if ((counter >= *(int *)(descriptor + 0x24)) && (*(char *)(animation + 2) == '\0')) {
    *(unsigned int *)(animation + 4) = 0;
    *(unsigned char *)(animation + 2) = 1;
  }
  if (*(char *)(animation + 2) == -1) {
    return 1;
  }
  return 0;
}
