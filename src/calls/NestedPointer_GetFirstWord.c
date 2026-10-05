int NestedPointer_GetFirstWord(int *objectBase, int recordIndex, int entryIndex)
{
    int *table = ((int **)(objectBase + recordIndex))[2];
    return table ? ((int **)(table + entryIndex))[1] : 0;
}
