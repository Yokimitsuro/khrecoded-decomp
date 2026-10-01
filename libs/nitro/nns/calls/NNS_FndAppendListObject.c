typedef struct NNSFndList {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

extern void SetFirstObject(NNSFndList *list, void *object);

void NNS_FndAppendListObject(NNSFndList *list, void *object)
{
    char *link;
    char *tailLink;

    if (list->head == 0) {
        SetFirstObject(list, object);
        return;
    }
    link = (char *)object + list->offset;
    *(void **)link = list->tail;
    *(void **)(link + 4) = 0;
    tailLink = (char *)list->tail + list->offset;
    *(void **)(tailLink + 4) = object;
    list->tail = object;
    list->count++;
}
