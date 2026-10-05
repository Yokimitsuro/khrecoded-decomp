typedef void code();
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void ReleaseCallbackOwnedBuffer(int object)

{
  if (*(code **)(object + 0x24) != (code *)0x0) {
    (**(code **)(object + 0x24))(object);
    if (*(int *)(object + 0xc) != 0) {
      NNSi_FndFreeFromDefaultHeap(*(int *)(object + 0xc));
    }
  }
  return;
}
