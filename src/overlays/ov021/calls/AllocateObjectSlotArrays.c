extern unsigned int NNSi_FndAllocFromDefaultHeap();

void AllocateObjectSlotArrays(int *container,int count)

{
  int index;
  
  container[1] = count;
  index = NNSi_FndAllocFromDefaultHeap(count * 0x2c);
  *container = index;
  index = NNSi_FndAllocFromDefaultHeap(count);
  container[2] = index;
  index = 0;
  if (0 < container[1]) {
    do {
      *(unsigned int *)(*container + index * 0x2c) = 0;
      *(signed char *)(container[2] + index) = -1;
      index = index + 1;
    } while (index < container[1]);
  }
  return;
}
