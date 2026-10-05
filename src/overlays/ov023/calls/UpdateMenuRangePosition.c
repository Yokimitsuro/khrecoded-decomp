extern unsigned int data_ov023_020b6f84;
extern unsigned int RemapIntoDisplayRange();

void UpdateMenuRangePosition(int minimum,int maximum,int value)

{
  unsigned int position;
  
  if (*(int *)(data_ov023_020b6f84 + 0x34) != 0) {
    position = RemapIntoDisplayRange(minimum,maximum,value);
    *(unsigned int *)(data_ov023_020b6f84 + 0x7fa8) = position;
  }
  return;
}
