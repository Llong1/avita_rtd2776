/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerSyncProcInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of ADC Clock Limit
//--------------------------------------------------
#define GET_ADC_LIMIT_CLOCK()                          (g_usAdcClockLimit)


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern WORD g_usAdcClockLimit;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerSyncProcScanInitial(void);
extern bit ScalerSyncProcPreDetect(void);
extern bit ScalerSyncProcStableDetect(void);
extern bit ScalerSyncProcGetSyncPad(void);
extern BYTE ScalerSyncProcTypeAutoRun(void);
extern bit ScalerSyncProcAdcClkInitial(void);
extern bit ScalerSyncProcAdcClkSetting(void);
extern void ScalerSyncProcClampPosCheck(BYTE ucVideoModeFlg);
extern void ScalerSyncProcClearSyncChangeStatus(void);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
extern void ScalerSyncProcSetPorchVoltage(void);
#endif

extern DWORD ScalerSyncProcGetCurrentClockFreq(void);

#endif // #if(_VGA_SUPPORT == _ON)

