extern int FX_Sqrt(int unknown_argument_x);

int MeasureVector4Length(int *vector)
{
    int component_0 = vector[0];
    int component_1 = vector[1];
    int component_2 = vector[2];
    int component_3 = vector[3];

    return FX_Sqrt((int)(((long long)component_0 * component_0 + 0x800) >> 12)
                 + (int)(((long long)component_1 * component_1 + 0x800) >> 12)
                 + (int)(((long long)component_2 * component_2 + 0x800) >> 12)
                 + (int)(((long long)component_3 * component_3 + 0x800) >> 12));
}
