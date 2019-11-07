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
// ID Code      : ScalerFRCInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define _PRE_READ_MEMORY                                    (3) // before DDEN line

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#define GET_DISP_LATENCY_RATIO()                            (g_ucDispLatecnyRatio)
#define SET_DISP_LATENCY_RATIO(x)                           (g_ucDispLatecnyRatio = (x))
#endif

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
extern BYTE g_ucDispLatecnyRatio;
#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
extern void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn);
#endif


//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
extern void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath, WORD usPreReadLine);
extern void ScalerFRCWaitWriteFrameBufFinish(void);
#endif

extern void ScalerFRCSetDDomainSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect);

