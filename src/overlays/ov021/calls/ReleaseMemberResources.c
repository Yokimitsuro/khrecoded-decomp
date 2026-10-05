typedef void code();
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void ReleaseMemberResources(int member,int context)

{
  if (*(code **)(member + 0x20) != (code *)0x0) {
    (**(code **)(member + 0x20))(member,context);
  }
  if (0 < *(int *)(member + 0x14)) {
    NNSi_FndFreeFromDefaultHeap(*(unsigned int *)(member + 0x10));
  }
  if (*(int *)(member + 0x1c) != 0) {
    NNSi_FndFreeFromDefaultHeap(*(unsigned int *)(member + 0x18));
  }
  return;
}
