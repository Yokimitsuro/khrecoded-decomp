extern void *NNS_FndGetNextListObject(void *pList, void *pObj);
extern void NNS_FndRemoveListObject(void *pList, void *pObj);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_0202c44c(void);
extern void func_ov027_020ba200(int *pNode, int nFlag);

extern int data_ov027_020ba3e4;

void func_ov027_020ba094(void)
{
    int *pNode;
    int *pQueue;
    int *pNext;

    pQueue = *(int **)&data_ov027_020ba3e4;
    pNode = (int *)NNS_FndGetNextListObject(pQueue, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pQueue, pNode);
        if (pNode[0] == 1) {
            func_0202c44c();
            if (pNode[2] != 0) {
                NNSi_FndFreeFromDefaultHeap((void *)pNode[2]);
            }
        }
        NNS_FndRemoveListObject(pQueue, pNode);
        if ((pNode[1] & 0x80000000) != 0) {
            pNode[1] = 0;
        } else if (pNode[1] != 0) {
            NNSi_FndFreeFromDefaultHeap((void *)pNode[1]);
        }
        if (pNode != 0) {
            NNSi_FndFreeFromDefaultHeap(pNode);
        }
        pNode = pNext;
    }

    pNode = (int *)NNS_FndGetNextListObject(pQueue + 3, 0);
    while (pNode != 0) {
        pNext = (int *)NNS_FndGetNextListObject(pQueue + 3, pNode);
        func_ov027_020ba200(pNode, 1);
        pNode = pNext;
    }
}
