#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollSegment;

typedef struct CollShape {
    CollSegment *segment;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

typedef struct ContactEntry {
    s32 value;
    s32 field;
    s32 unk_08;
} ContactEntry;

typedef struct ContactSlot {
    s32 value;
    s32 field;
    u8 surfaceType;
    u8 pad_09[3];
} ContactSlot;

typedef struct ContactList {
    ContactSlot slots[16];
    VecFx32 normals[16];
    u8 count;
} ContactList;

typedef struct Mover {
    u8 pad_00[0x7c];
    u8 hasSweep;
    u8 pad_7d[0x33];
    CollSweep *sweep;
    ContactList *contacts;
    u8 recordsContacts;
    u8 replaceSlot;
} Mover;

typedef struct MotionQueue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
} MotionQueue;

typedef void (*ShapeBoundsFn)(CollShape *shape, CollBox *box);

extern ShapeBoundsFn gCollisionBoundsDispatch[];
extern ContactPlane data_027e0148;
extern MotionQueue data_027e0134;

extern s32 DispatchContactCallbacks(Mover *mover, ContactEntry *entry, s32 index, BOOL *moving, ContactPlane *planes, ContactEntry *entries);
extern void PushContact(ContactList *list, s32 value, s32 field, u8 surfaceType, VecFx32 *normal);
extern void SetMotionQueueField(ContactEntry *entry);
extern void OffsetBoxByDelta(const CollBox *src, CollBox *dst, const VecFx32 *delta);
extern void InitSegmentFromEndpoints(CollSegment *segment);
extern void GetSegmentPointAtHitTime(VecFx32 *out, ContactPlane *plane, CollSegment *segment);
extern void ScaleVecHighShift(VecFx32 *vec, s32 scale);

s32 RecordContactPlane(Mover *mover, s32 index, ContactPlane *planes, ContactEntry *entries, ContactEntry *entry, BOOL *moving)
{
    BOOL stopped = FALSE;
    BOOL recorded;
    s32 result;

    result = DispatchContactCallbacks(mover, entry, index, moving, planes, entries);
    if (result != 1) {
        return result;
    }
    if (planes == NULL) {
        mover->contacts->slots[mover->contacts->count].value = entry->value;
        mover->contacts->slots[mover->contacts->count].field = entry->field;
        mover->contacts->count++;
        return 2;
    }
    if (!mover->recordsContacts) {
        recorded = FALSE;
    } else {
        if (mover->hasSweep) {
            if (*moving) {
                VecFx32 delta;
                CollSweep *sweep;
                fx32 time = planes[index].time;

                delta = mover->sweep->delta;
                ScaleVecHighShift(&delta, time);
                sweep = mover->sweep;
                sweep->delta = delta;
                OffsetBoxByDelta(&sweep->shape.box, &sweep->sweepBox, &sweep->delta);
                if (mover->sweep->delta.x == 0 && mover->sweep->delta.y == 0 && mover->sweep->delta.z == 0) {
                    stopped = TRUE;
                }
            } else {
                stopped = TRUE;
            }
        } else {
            VecFx32 end;
            CollSweep *sweep;

            GetSegmentPointAtHitTime(&end, &planes[index], mover->sweep->shape.segment);
            mover->sweep->shape.segment->end = end;
            InitSegmentFromEndpoints(mover->sweep->shape.segment);
            sweep = mover->sweep;
            gCollisionBoundsDispatch[sweep->shape.kind](&sweep->shape, &sweep->shape.box);
            if (mover->sweep->shape.segment->length == 0) {
                stopped = TRUE;
            }
        }
        data_027e0148 = planes[index];
        recorded = TRUE;
    }
    if (recorded) {
        if (mover->contacts->count == mover->replaceSlot) {
            PushContact(mover->contacts, entry->value, entry->field, planes[index].surfaceType, &planes[index].normal);
        } else {
            mover->contacts->slots[mover->replaceSlot].value = entry->value;
            mover->contacts->slots[mover->replaceSlot].field = entry->field;
            mover->contacts->slots[mover->replaceSlot].surfaceType = planes[index].surfaceType;
            mover->contacts->normals[mover->replaceSlot] = planes[index].normal;
            data_027e0134.unk_04 = 0;
            data_027e0134.unk_08 = 0;
            data_027e0134.unk_0c = 0;
            data_027e0134.unk_10 = 0;
        }
        SetMotionQueueField(entry);
        if (stopped) {
            return 2;
        }
        return 0;
    }
    if (!mover->recordsContacts) {
        entries[index] = *entry;
        return 1;
    }
    return stopped ? 2 : 1;
}
