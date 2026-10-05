void UnlinkDoublyLinkedNode(int **listHead, int *removedNode) {
    if (removedNode[0] != 0) {
        *(int *)(removedNode[0] + 4) = removedNode[1];
    }
    if (removedNode[1] != 0) {
        *(int *)removedNode[1] = removedNode[0];
    }
    if (removedNode == *listHead) {
        *listHead = (int *)removedNode[0];
    }
    removedNode[1] = 0;
    removedNode[0] = 0;
}
