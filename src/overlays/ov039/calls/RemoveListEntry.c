extern int data_ov039_020bea20;
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNS_FndRemoveListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void RemoveListEntry(void *entry)
{
    void *current = NNS_FndGetNextListObject((void *)(data_ov039_020bea20 + 0xca74), 0);

    while (current != 0) {
        if (current == entry) {
            NNS_FndRemoveListObject((void *)(data_ov039_020bea20 + 0xca74), entry);
            if (entry != 0) {
                NNSi_FndFreeFromDefaultHeap(entry);
            }
            return;
        }
        current = NNS_FndGetNextListObject((void *)(data_ov039_020bea20 + 0xca74), current);
    }
}
