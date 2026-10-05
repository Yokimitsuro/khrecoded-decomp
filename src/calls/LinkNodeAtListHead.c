void LinkNodeAtListHead(int *listHead, int *newNode)
{
    newNode[1] = 0;
    newNode[0] = *listHead;
    if (*listHead != 0)
        *(int *)(*listHead + 4) = (int)newNode;
    *listHead = (int)newNode;
}
