extern void QuadTree_RemoveObject(int *tree, int node);
extern void QuadTree_InsertObject(int *tree, int node);

/* Re-inserts a node if its moved flag is set */
void QuadTree_ReinsertNodeIfFlagSet(int *tree, int node) {
    if ((*(unsigned char *)(node + 0xc) & 1) == 0) {
        return;
    }
    QuadTree_RemoveObject(tree, node);
    QuadTree_InsertObject(tree, node);
    *(unsigned char *)(node + 0xc) =
        *(unsigned char *)(node + 0xc) & 0xfe;
}
