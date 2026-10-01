typedef struct NNSFndList {
    void *head;
    void *tail;
    unsigned short count;
    unsigned short offset;
} NNSFndList;

extern void SetFirstObject(NNSFndList *list, void *object);

void NNS_FndPrependListObject(NNSFndList *list, void *object)
{
    char *link;
    char *headLink;

    if (list->head == 0) {
        SetFirstObject(list, object);
        return;
    }
    link = (char *)object + list->offset;
    *(void **)link = 0;
    *(void **)(link + 4) = list->head;
    headLink = (char *)list->head + list->offset;
    *(void **)headLink = object;
    list->head = object;
    list->count++;
}
