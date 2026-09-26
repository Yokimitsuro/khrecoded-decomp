typedef int (*Unk0205137cCallback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk0205137cEntry;

extern int data_ov039_020beaa4[];
extern Unk0205137cEntry data_ov039_020be950[];

int func_ov039_020bced0(int arg0)
{
    int result = 1;
    int index = data_ov039_020beaa4[0];

    if (index != -1) {
        result = (*(Unk0205137cCallback *)data_ov039_020be950[index].object)(arg0);
    }

    return result;
}
