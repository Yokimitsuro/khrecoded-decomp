extern int data_ov039_020bea20;
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void RemoveListEntry(void *entry);

void DestroyAllListEntries(void)
{
    void *entry = NNS_FndGetNextListObject((void *)(data_ov039_020bea20 + 0xca74), 0);
    void *next;

    if (entry == 0) {
        return;
    }
    do {
        next = NNS_FndGetNextListObject((void *)(data_ov039_020bea20 + 0xca74), entry);
        RemoveListEntry(entry);
        entry = next;
    } while (next != 0);
}
