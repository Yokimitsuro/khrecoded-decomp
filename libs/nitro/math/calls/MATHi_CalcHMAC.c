typedef unsigned char u8;
typedef unsigned int u32;

typedef struct MATHiHMACFuncs {
    u32 digestLength;
    u32 blockLength;
    void *context;
    u8 *hashBuffer;
    void (*HashReset)(void *context);
    void (*HashSetSource)(void *context, const void *source, u32 length);
    void (*HashGetDigest)(void *context, void *digest);
} MATHiHMACFuncs;

#define MATH_HASH_BLOCK_SIZE 64

void MATHi_CalcHMAC(
    void *mac,
    const void *message,
    u32 messageLength,
    const void *key,
    u32 keyLength,
    MATHiHMACFuncs *functions)
{
    int i;
    u8 newKey[MATH_HASH_BLOCK_SIZE];
    u8 *useKey;
    u32 useKeyLength;
    u8 innerKey[MATH_HASH_BLOCK_SIZE];
    u8 outerKey[MATH_HASH_BLOCK_SIZE];

    if (mac == 0 || message == 0 || messageLength == 0 ||
        key == 0 || keyLength == 0 || functions == 0) {
        return;
    }

    if (keyLength > functions->blockLength) {
        functions->HashReset(functions->context);
        functions->HashSetSource(functions->context, key, keyLength);
        functions->HashGetDigest(functions->context, newKey);
        useKey = newKey;
        useKeyLength = functions->digestLength;
    } else {
        useKey = (u8 *)key;
        useKeyLength = keyLength;
    }

    for (i = 0; i < useKeyLength; i++) {
        innerKey[i] = useKey[i] ^ 0x36;
    }
    for (; i < functions->blockLength; i++) {
        innerKey[i] = 0x36;
    }

    functions->HashReset(functions->context);
    functions->HashSetSource(functions->context, innerKey, functions->blockLength);
    functions->HashSetSource(functions->context, message, messageLength);
    functions->HashGetDigest(functions->context, functions->hashBuffer);

    for (i = 0; i < useKeyLength; i++) {
        outerKey[i] = useKey[i] ^ 0x5c;
    }
    for (; i < functions->blockLength; i++) {
        outerKey[i] = 0x5c;
    }

    functions->HashReset(functions->context);
    functions->HashSetSource(functions->context, outerKey, functions->blockLength);
    functions->HashSetSource(functions->context, functions->hashBuffer, functions->digestLength);
    functions->HashGetDigest(functions->context, mac);
}