#pragma thumb on

void func_0202fde0(int **head, int *node) {
    if (node[0] != 0) {
        *(int *)(node[0] + 4) = node[1];
    }
    if (node[1] != 0) {
        *(int *)node[1] = node[0];
    }
    if (node == *head) {
        *head = (int *)node[0];
    }
    node[1] = 0;
    node[0] = 0;
}
