extern int data_02060394;

void *SetDefaultHeap(void *heap) {
    void *previous = *(void **)((char *)&data_02060394 + 4);
    *(void **)((char *)&data_02060394 + 4) = (heap == 0) ? *(void **)((char *)&data_02060394 + 8) : heap;
    return previous;
}
