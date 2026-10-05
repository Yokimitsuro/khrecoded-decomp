extern unsigned int Anim_GetFrame();

int GetMaximumFieldValue(unsigned int object)

{
  int value;
  unsigned int index;
  int maximum;
  
  maximum = 0;
  index = 0;
  do {
    value = Anim_GetFrame(object,index & 0xffff);
    if (value > maximum) {
      maximum = value;
    }
    index = index + 1;
  } while ((int)index < 5);
  return maximum;
}
