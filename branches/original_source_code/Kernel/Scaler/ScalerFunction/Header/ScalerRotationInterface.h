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

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerRotationInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define GET_ROT_TYPE()                                  (g_stRotationStatus.enumRotationType)
#define SET_ROT_TYPE(x)                                 (g_stRotationStatus.enumRotationType = (x))

#define GET_ROT_DISP_SIZE()                             (g_stRotationStatus.enumRotationDispSize)
#define SET_ROT_DISP_SIZE(x)                            (g_stRotationStatus.enumRotationDispSize = (x))

//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern StructRotationStatus g_stRotationStatus;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern bit ScalerRotationCheckStatus(void);
extern void ScalerRotationSetDDomainSourceSelect(EnumDDomainSourceSelect enumSourceSelect);
extern void ScalerRotationSetFRCEn(EnumFRCOnOff enumCapDispOnOff, bit bEn);
#endif

