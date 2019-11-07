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
// ID Code      : ScalerSyncProcInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Sync Processor Clock Frequency
//--------------------------------------------------
#define _SYNC_PRO_CLK_DIV                           (ScalerGetBit(P40_06_SYNCPROC_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) // Sync Pro Clock Divider
#define _SYNC_PRO_USE_M2PLL_CLK                     ((bit)ScalerGetBit(P40_06_SYNCPROC_CLK_DIVIDER, _BIT4) ? _TRUE : _FALSE)
#define _SYNC_PRO_XTAL_CLK                          ((bit)ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) ? _INTERNAL_OSC_XTAL : _EXT_XTAL)
#define _SYNC_PROC_CLK                              (DWORD)((bit)ScalerGetBit(P1_E5_M2PLL_WD, _BIT0) ? _SYNC_PRO_XTAL_CLK : (_SYNC_PRO_USE_M2PLL_CLK ? (((DWORD)_M2PLL_CLK_KHZ) / _SYNC_PRO_CLK_DIV) : _SYNC_PRO_XTAL_CLK))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerSyncProcScanInitial(void);
extern WORD ScalerSyncProcGetDeVsyncWidth(void);
extern WORD ScalerSyncProcGetClampEndPosition(void);
extern WORD ScalerSyncProcMeasureIHFreqByStableMeasure(void);
extern void ScalerSyncProcPulseDetectEnable(BYTE ucEnable);
extern void ScalerSyncProcSetDebounce(BYTE ucDebounce);

#endif // End of #if(_VGA_SUPPORT == _ON)

