extern unsigned int *data_ov032_020c0088[];
#define puRam020c006c data_ov032_020c0088[1]
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void ReleaseGroupResourceBuffers(void)

{
  unsigned int *buffers;
  
  buffers = puRam020c006c;
  NNSi_FndFreeFromDefaultHeap(*puRam020c006c);
  NNSi_FndFreeFromDefaultHeap(buffers[1]);
  NNSi_FndFreeFromDefaultHeap(buffers[2]);
  NNSi_FndFreeFromDefaultHeap(buffers[3]);
  puRam020c006c = (unsigned int *)0x0;
  return;
}
