extern int MeasureVector4Length(int *source_vector);
extern long long FX_InvFx64c(int unknown_argument_x);

int ScaleVector4ByReciprocalMagnitude(int *vector, int *source_vector)
{
    int magnitude = MeasureVector4Length(source_vector);

    if (magnitude != 0) {
        long long reciprocal = FX_InvFx64c(magnitude);
        vector[0] = (int)((reciprocal * vector[0] + 0x80000000LL) >> 32);
        vector[1] = (int)((reciprocal * vector[1] + 0x80000000LL) >> 32);
        vector[2] = (int)((reciprocal * vector[2] + 0x80000000LL) >> 32);
        vector[3] = (int)((reciprocal * vector[3] + 0x80000000LL) >> 32);
    } else {
        vector[0] = 0;
        vector[1] = 0;
        vector[2] = 0;
        vector[3] = 0;
    }
    return magnitude;
}
