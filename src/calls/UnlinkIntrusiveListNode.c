void UnlinkIntrusiveListNode(int *listHead, int *node) {
    if (node == (int *)*listHead) *listHead = node[1];
    if ((int *)node[1] != (int *)0) *(int *)node[1] = *node;
    if (*node != 0) *(int *)(*node + 4) = node[1];
    *node = 0;
    node[1] = 0;
}
