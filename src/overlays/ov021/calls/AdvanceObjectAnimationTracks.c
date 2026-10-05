extern unsigned int AdvanceAnimationTracks();

void AdvanceObjectAnimationTracks(unsigned int *object,unsigned int delta)

{
  short status;
  
  if ((*object & 1) != 0) {
    if (object[0x43] != 0) {
      AdvanceAnimationTracks(object + 2,delta);
    }
    if (((*object & 0x400) != 0) &&
       (status = AdvanceAnimationTracks(object[0x8a],delta), (status & 1) != 0)) {
      *object = *object & 0xfffffbff;
    }
  }
  return;
}
