extern int gScriptState;

int LoadGlobalS8At0(void) {
    return *(signed char *)&gScriptState;
}
