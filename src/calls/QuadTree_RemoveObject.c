extern void UnlinkNodeFromList(int);

void QuadTree_RemoveObject(int *param_1, int param_2) {
    if (param_1[0x27] == 0) {
        return;
    }
    UnlinkNodeFromList(param_2);
}
