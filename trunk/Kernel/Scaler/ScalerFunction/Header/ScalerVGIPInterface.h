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
// ID Code      : ScalerVGIPInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_VGIP_INPUT_PATH()                       (g_enumVgipInputPath)
#define CHK_VGIP_INPUT_PATH(x)                      ((g_enumVgipInputPath & (x)) == (x))

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern EnumInputDataPath g_enumVgipInputPath;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerVgipSetInputRegion(EnumDisplayRegion enumDisplayRegion);
extern void ScalerVgipSetInputPath(EnumInputDataPath enumVgipInputPath);
extern WORD ScalerVgipGetCaptureHStartPosition(void);

#if(_OVERSCAN_SUPPORT == _ON)
extern WORD ScalerVgipGetCaptureHWidth(void);
#endif
extern WORD ScalerVgipGetCaptureHDelay(void);
extern void ScalerVgipSetCaptureHDelay(WORD usIHSDelay);

extern bit ScalerVgipGetDigitalCaptureStatus(void);
