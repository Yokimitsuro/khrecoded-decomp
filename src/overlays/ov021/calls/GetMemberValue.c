

unsigned int GetMemberValue(int *container,int index)

{
  int entry;
  
  if (index >= container[1]) {
    return 0;
  }
  entry = *(int *)(*container + index * 4);
  if (entry == 0) {
    return 0;
  }
  return *(unsigned int *)(entry + 4);
}
