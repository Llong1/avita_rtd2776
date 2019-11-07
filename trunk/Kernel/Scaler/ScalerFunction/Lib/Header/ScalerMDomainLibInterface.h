/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerMDomainLibInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_PIXEL_SHIFT_SUPPORT == _ON)
extern void ScalerMDomainSetDisplayTimingGenBackgroundVStart(BYTE ucBGVStart_H, BYTE ucBGVStart_L, EnumDBApply enumDBApply);
extern WORD ScalerMDomainGetDisplayTimingGenBackgroundVStart(void);
extern void ScalerMDomainSetDisplayTimingGenBackgroundVEnd(BYTE ucBGVEnd_H, BYTE ucBGVEnd_L, EnumDBApply enumDBApply);
extern WORD ScalerMDomainGetDisplayTimingGenBackgroundVEnd(void);
extern void ScalerMDomainSetDisplayTimingGenActiveRegionHStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply);
extern WORD ScalerMDomainGetDisplayTimingGenActiveRegionHStart(void);
extern WORD ScalerMDomainGetDisplayTimingGenActiveRegionHEnd(void);
extern void ScalerMDomainSetDisplayTimingGenActiveRegionVStart(BYTE ucActHStart_H, BYTE ucActHStart_L, EnumDBApply enumDBApply);
extern WORD ScalerMDomainGetDisplayTimingGenActiveRegionVStart(void);
extern WORD ScalerMDomainGetDisplayTimingGenActiveRegionVEnd(void);
extern void ScalerMDomainSetCaptureWindowEnable(bit bCapWinEnable);
extern void ScalerMDomainSetCaptureWindowHStart(BYTE ucCapWinHStart_H, BYTE ucCapWinHStart_L);
extern WORD ScalerMDomainGetCaptureWindowHStart(void);
extern void ScalerMDomainSetCaptureWindowHEnd(BYTE ucCapWinHEnd_H, BYTE ucCapWinHEnd_L);
extern WORD ScalerMDomainGetCaptureWindowHEnd(void);
extern void ScalerMDomainSetCaptureWindowVStart(BYTE ucCapWinVStart_H, BYTE ucCapWinVStart_L);
extern WORD ScalerMDomainGetCaptureWindowVStart(void);
extern void ScalerMDomainSetCaptureWindowVEnd(BYTE ucCapWinVEnd_H, BYTE ucCapWinVEnd_L);
#endif

