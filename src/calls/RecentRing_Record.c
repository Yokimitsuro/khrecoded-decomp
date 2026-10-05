extern int data_0206084c;

typedef struct {
    unsigned short id;
    unsigned char kind;
    unsigned char stamp;
} RingSlot;

typedef struct {
    RingSlot slots[32];
    unsigned short from;
    unsigned short count;
    unsigned char tick;
} RingQueue;

int RecentRing_Record(unsigned short id, unsigned char kind)
{
    RingQueue *q = (RingQueue *)(*(int *)&data_0206084c + 739128);
    unsigned short i = 0;
    unsigned short count = q->count;
    RingSlot *slot;

    for (; i < count; i++) {
        slot = &q->slots[(q->from + i) & 0x1f];
        if (slot->id == id && slot->kind == kind) {
            return 0;
        }
    }
    if (count == 32) {
        unsigned short from = q->from;

        q->from = (from + 1) & 0x1f;
        slot = &q->slots[from];
    } else {
        slot = &q->slots[(q->from + count) & 0x1f];
        q->count++;
    }
    slot->id = id;
    slot->kind = kind;
    slot->stamp = q->tick;
    return 1;
}
