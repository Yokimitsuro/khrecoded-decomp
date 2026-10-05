int ScriptValue_ToScalar(short *typedValue) {
    int convertedValue = 0;
    if (*typedValue == 1) convertedValue = *(int *)(typedValue + 2) << 0xc;
    else if (*typedValue != 2) convertedValue = *(int *)(typedValue + 2);
    return convertedValue;
}
