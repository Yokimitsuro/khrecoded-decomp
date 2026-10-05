extern void MIi_CpuClear32(unsigned int data, void *dst, unsigned int size);
extern void DetachObjectTreeNode(void *child);
extern void strcpy(void *dst, void *src);
extern int NNS_G3dGetResDictIdxByName(void *resourceEntry, void *searchKey);

extern char data_02060770[];

void attach_child_object(void *child, void *parent, void *initializationData) {
    int resourceIndex;
    void *resourceEntry;

    if (((void **)child)[0xbc / 4] != (void *)0) {
        DetachObjectTreeNode(child);
    }
    if (parent == (void *)0) return;

    MIi_CpuClear32(0, data_02060770, 0x10);
    strcpy(data_02060770, initializationData);

    resourceEntry = ((void **)parent)[0x24 / 4];
    resourceEntry = resourceEntry ? (void *)((char *)resourceEntry + 0x40) : (void *)0;
    if (resourceEntry == (void *)0) {
        resourceIndex = -1;
    } else {
        resourceIndex = NNS_G3dGetResDictIdxByName(resourceEntry, data_02060770);
    }
    *(unsigned short *)((char *)child + 0xc8) = (unsigned short)resourceIndex;

    {
        void *previousFirstChild = ((void **)parent)[0xc0 / 4];
        if (previousFirstChild != (void *)0) ((void **)child)[0xc4 / 4] = previousFirstChild;
    }
    ((void **)parent)[0xc0 / 4] = child;
    ((void **)child)[0xbc / 4] = parent;
}
