

unsigned int IsSupportedOwnerState(unsigned int context,int *owner)

{
  if (owner != (int *)0x0) {
    if ((owner[1] == 2) && (*(int *)(*owner + 4) == 2)) {
      return 1;
    }
    if (owner[1] - 0x10U <= 1) {
      return 1;
    }
  }
  return 0;
}
