extern unsigned int data_ov031_020bc820;
extern unsigned int func_ov043_020bca3c();

int GetNegatedCombinedOffset(int offset)

{
  int context;
  int record;
  
  context = data_ov031_020bc820;
  record = func_ov043_020bca3c();
  { int value = *(int *)(*(int *)(context + 0x50) + *(int *)(context + 0x44) * 0x3c);
    value += *(int *)(record + 8);
    return -(offset + value); }
}
