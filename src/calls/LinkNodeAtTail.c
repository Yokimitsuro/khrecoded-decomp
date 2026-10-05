void LinkNodeAtTail(int **listHead, int **tailLink, int **newNode) {
    int *oldTail;
    newNode[1] = (int *)tailLink;
    oldTail = tailLink[0];
    newNode[0] = oldTail;
    if (oldTail == 0) {
        listHead[0] = (int *)newNode;
    } else {
        oldTail[1] = (int)newNode;
    }
    tailLink[0] = (int *)newNode;
}
