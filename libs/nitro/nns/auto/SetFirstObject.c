typedef struct NNSFndList {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

void SetFirstObject(NNSFndList *list, void *object)
{
    char *link = (char *)object + list->offset;

    *(void **)(link + 4) = 0;
    *(void **)link = 0;
    list->head = object;
    list->tail = object;
    list->count++;
}
