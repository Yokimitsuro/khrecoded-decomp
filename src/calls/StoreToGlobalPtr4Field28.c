extern int gTaskManager;

void StoreToGlobalPtr4Field28(int arg0) {
    *(int *)(*(int *)((char *)&gTaskManager + 4) + 0x28) = arg0;
}
