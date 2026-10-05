#include "nitro/types.h"

typedef struct {
    u8 opaque[0x60];
} HashContext;

extern void DGT_Hash2Reset(HashContext *ctx);
extern void DGT_Hash2SetSource(HashContext *ctx, const void *data, u32 len);
extern void DGT_Hash2GetDigest(HashContext *ctx, void *digest);

/* one-shot SHA-1-style digest of a buffer */
void ComputeHash(void *digest, const void *data, u32 len, u32 unused)
{
    HashContext ctx;

    DGT_Hash2Reset(&ctx);
    DGT_Hash2SetSource(&ctx, data, len);
    DGT_Hash2GetDigest(&ctx, digest);
}
