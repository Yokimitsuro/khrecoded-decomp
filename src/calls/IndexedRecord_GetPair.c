int IndexedRecord_GetPair(int recordBase, int recordIndex)
{
    if (recordIndex < 0)
        return 0;
    return recordBase + 0x10 + recordIndex * 0x8c;
}
