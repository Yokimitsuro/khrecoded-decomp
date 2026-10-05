typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Entry {
    char pad_0000[8];
    VecFx32 pos;
} Entry;

typedef struct Hit {
    char pad_0000[0x2c];
    int distance2c;
} Hit;

extern Entry *CollModel_FindEntry(void *cont);
extern Hit *QueryCollisionSegment(void *world, VecFx32 *from, VecFx32 *dir);
extern void AddScaledVector(int s, const VecFx32 *dir, const VecFx32 *from, VecFx32 *out);

int ProjectPositionDownward(void *cont, int p3, void *out) {
    Entry *entry = CollModel_FindEntry(cont);
    VecFx32 from;
    VecFx32 dir;
    Hit *hit;

    from.x = entry->pos.x;
    from.y = entry->pos.y + 0x1000;
    from.z = entry->pos.z;
    dir.x = 0;
    dir.y = -0x5000;
    dir.z = 0;

    hit = QueryCollisionSegment(cont, &from, &dir);
    if (hit != 0) {
        AddScaledVector(hit->distance2c, &dir, &from, (VecFx32 *)out);
        return 1;
    }
    *(VecFx32 *)out = entry->pos;
    return 0;
}
