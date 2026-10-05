extern int data_020603c8[];
extern int data_020603d8[];

void unlink_object_registry_node(int node)
{
    unsigned int nodeKey;
    int nextNode;
    int bucketHead;

    nodeKey = *(unsigned short *)(node + 0x10);
    if (data_020603c8[3] == node) {
        data_020603c8[3] = *(int *)(node + 0xc);
    }
    bucketHead = data_020603d8[nodeKey];
    if (bucketHead == node) {
        nextNode = *(int *)(node + 0xc);
        if (nextNode != 0 && *(unsigned short *)(nextNode + 0x10) == nodeKey) {
            data_020603d8[nodeKey] = nextNode;
        } else {
            data_020603d8[nodeKey] = 0;
        }
    }
    if (*(int *)(node + 0xc) != 0) {
        *(int *)(*(int *)(node + 0xc) + 8) = *(int *)(node + 8);
    }
    if (*(int *)(node + 8) != 0) {
        *(int *)(*(int *)(node + 8) + 0xc) = *(int *)(node + 0xc);
    }
}
