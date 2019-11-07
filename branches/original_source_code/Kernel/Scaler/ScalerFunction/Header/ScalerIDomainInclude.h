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
// ID Code      : ScalerIDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_VGIP_INITIAL_VDELAY()                   (g_usVgipVDelayInitial)
#define SET_VGIP_INITIAL_VDELAY(x)                  (g_usVgipVDelayInitial = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usVgipVDelayInitial;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerIDomainVgipAdjustIHVDelay(void);
extern void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture);
extern void ScalerIDomainResetDataPath(EnumInputDataPath enumVgipInputPath);

