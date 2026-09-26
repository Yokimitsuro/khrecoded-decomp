typedef int (*Unk02051458Callback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk02051458Entry;

extern int data_ov039_020beaa4[];
extern Unk02051458Entry data_ov039_020be8f0[];

int func_ov039_020bcfec(int arg0)
{
    int result = 1;
    int index = data_ov039_020beaa4[1];

    if (index != -1) {
        result = (*(Unk02051458Callback *)data_ov039_020be8f0[index].object)(arg0);
    }

    return result;
}
