int func_ov022_020a9cd0(int ctx) {
    int extra;
    int i;

    if ((unsigned int)*(int *)(ctx + 0x9c) > (unsigned int)*(int *)(ctx + 0xa0)) {
        return 0;
    }

    if ((*(unsigned short *)**(int **)(ctx + 0x34) & 0x8000) != 0) {
        *(int *)(ctx + 0xa4) = 1;
        extra = 4;
    } else {
        extra = 0;
        *(int *)(ctx + 0xa4) = 0;
    }

    **(int **)(ctx + 0x34) += (*(int (**)(int))(ctx + 0x38))(*(int *)(ctx + 0x34));

    if (*(signed char *)(ctx + 8) == 0x4e && *(signed char *)(ctx + 9) == 0x33) {
        **(int **)(ctx + 0x34) += extra;
    }

    *(int *)(*(int *)(ctx + 0x64) + *(int *)(ctx + 0xac) * 4) =
        *(int *)(*(int *)(ctx + 0x34) + 0x3b4);
    *(int *)(ctx + 0xcc) = 0;
    *(int *)(ctx + 0xd0) = 0;

    for (i = 0; i < 6; i++) {
        ((int *)ctx)[i + 0x2b] = ((int *)ctx)[i + 0x2b] + 1;
        if (*(int *)(ctx + 0xa8) == ((int *)ctx)[i + 0x2b]) {
            ((int *)ctx)[i + 0x2b] = 0;
        }
    }

    *(int *)(ctx + 0xa0) = *(int *)(ctx + 0xa0) + 1;
    return 1;
}
