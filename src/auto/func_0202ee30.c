void func_0202ee30(int obj) {
    int cur, prev;
    if (*(int *)(obj + 0xbc) != 0) {
        prev = 0;
        cur = *(int *)(*(int *)(obj + 0xbc) + 0xc0);
        while (cur != 0) {
            if (cur == obj) {
                if (prev != 0) {
                    *(int *)(prev + 0xc4) = *(int *)(cur + 0xc4);
                } else {
                    *(int *)(*(int *)(obj + 0xbc) + 0xc0) = *(int *)(cur + 0xc4);
                }
            }
            prev = cur;
            cur = *(int *)(cur + 0xc4);
        }
        *(int *)(obj + 0xbc) = 0;
    }
    {
        int c = *(int *)(obj + 0xc0);
        if (c != 0) {
            while (c != 0) {
                *(int *)(c + 0xbc) = 0;
                c = *(int *)(c + 0xc4);
            }
            *(int *)(obj + 0xc0) = 0;
        }
    }
}
