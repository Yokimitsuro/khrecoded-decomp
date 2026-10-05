int GetField4UnlessState2(int arg0) {
    return (*(short *)arg0 == 2) ? 0 : *(int *)(arg0 + 4);
}
