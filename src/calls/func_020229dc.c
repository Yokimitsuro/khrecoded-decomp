extern int __msl_mktime(void *buffer, int *result);

typedef struct {
    int words[9];
} Blob36;

int func_020229dc(Blob36 *ptr, int unused1, int unused2, int unused3)
{
    Blob36 local;
    int result;

    local = *ptr;
    if (__msl_mktime(&local, &result) != 0) {
        *ptr = local;
        return result;
    }
    return -1;
}
