void DetachObjectTreeNode(int node) {
    int child, previousChild;
    if (*(int *)(node + 0xbc) != 0) {
        previousChild = 0;
        child = *(int *)(*(int *)(node + 0xbc) + 0xc0);
        while (child != 0) {
            if (child == node) {
                if (previousChild != 0) {
                    *(int *)(previousChild + 0xc4) = *(int *)(child + 0xc4);
                } else {
                    *(int *)(*(int *)(node + 0xbc) + 0xc0) = *(int *)(child + 0xc4);
                }
            }
            previousChild = child;
            child = *(int *)(child + 0xc4);
        }
        *(int *)(node + 0xbc) = 0;
    }
    {
        int childCursor = *(int *)(node + 0xc0);
        if (childCursor != 0) {
            while (childCursor != 0) {
                *(int *)(childCursor + 0xbc) = 0;
                childCursor = *(int *)(childCursor + 0xc4);
            }
            *(int *)(node + 0xc0) = 0;
        }
    }
}
