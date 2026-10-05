extern unsigned int func_ov043_020bca3c();

unsigned int IsOffsetBeyondActiveRecord(int firstOffset,int secondOffset)

{
  int record;
  
  record = func_ov043_020bca3c();
  if (firstOffset - secondOffset > *(int *)(record + 8)) {
    return 1;
  }
  return 0;
}
