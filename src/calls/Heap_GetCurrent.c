extern int data_02060394;

int Heap_GetCurrent(void) {
    return *(int *)((char *)&data_02060394 + 4);
}
