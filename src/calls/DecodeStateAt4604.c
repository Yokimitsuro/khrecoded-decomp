int DecodeStateAt4604(int object) {
    if (*(int *)(object + 0x4604) != 1) {
        if (*(int *)(object + 0x4604) == 2) object = 2;
        return object;
    }
    return 1;
}
