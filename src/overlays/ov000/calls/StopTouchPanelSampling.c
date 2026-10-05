extern void TP_RequestAutoSamplingStopAsync(void);
extern void TP_WaitBusy(int channel);
extern void TP_CheckError(int channel);

void StopTouchPanelSampling(void)
{
    TP_RequestAutoSamplingStopAsync();
    TP_WaitBusy(4);
    TP_CheckError(4);
}
