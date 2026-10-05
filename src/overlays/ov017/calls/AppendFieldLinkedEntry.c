extern unsigned int FindLinkedEntryTail();
extern unsigned int FindLastLoopEntry();

void AppendFieldLinkedEntry(int *head,int entry)

{
  int tail;
  int lastEntry;
  unsigned int firstEntry;
  
  if (*head == 0) {
    *head = entry;
    if ((*(unsigned char *)(entry + 1) & 1) != 0) {
      *(int *)(entry + 4) = entry;
    }
    else {
      *(unsigned int *)(entry + 4) = 0;
    }
    *(unsigned char *)(entry + 1) = *(unsigned char *)(entry + 1) | 2;
    return;
  }
  tail = FindLinkedEntryTail(*head);
  lastEntry = FindLinkedEntryTail(entry);
  if (tail != 0) {
    *(unsigned char *)(tail + 1) = *(unsigned char *)(tail + 1) & 0xfd;
  }
  *(unsigned char *)(lastEntry + 1) = *(unsigned char *)(lastEntry + 1) | 2;
  *(int *)(tail + 4) = entry;
  *(unsigned int *)(lastEntry + 4) = 0;
  firstEntry = FindLastLoopEntry(*head);
  *(unsigned int *)(lastEntry + 4) = firstEntry;
  return;
}
