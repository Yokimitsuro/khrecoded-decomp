int IndexedRecord_SetActive(int recordBase, int recordIndex)
{
    int *recordFlags;
    if (recordIndex < 0)
        return recordBase;
    recordFlags = (int *)(recordBase + 0x7c + recordIndex * 0x8c);
    return *recordFlags |= 2;
}
