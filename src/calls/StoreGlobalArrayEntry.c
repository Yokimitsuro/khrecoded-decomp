extern int data_02055e04;

void StoreGlobalArrayEntry(int index, int value) {
    ((int *)&data_02055e04)[index] = value;
}
