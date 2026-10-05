extern unsigned int Flags16_ClearBit1();
extern unsigned int Flags16_SetBit1();

void SetObjectAnimationEnabled(unsigned int *object,int enabled)

{
  if ((*object & 1) != 0) {
    if (enabled != 0) {
      Flags16_SetBit1(object + 2);
      if (object[0x8a] != 0) {
        Flags16_SetBit1(object[0x8a]);
      }
    }
    else {
      Flags16_ClearBit1(object + 2);
      if (object[0x8a] != 0) {
        Flags16_ClearBit1(object[0x8a]);
        return;
      }
    }
  }
  return;
}
