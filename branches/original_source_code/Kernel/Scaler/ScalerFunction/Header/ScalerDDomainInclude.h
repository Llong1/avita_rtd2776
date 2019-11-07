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
// ID Code      : ScalerDDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern BYTE g_ucDDomainPanelIndex;
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerDDomainGetBackgroundStatus(EnumDisplayDataPath enumDisplayDataPath);
extern void ScalerDDomainBackgroundEnable(EnumDisplayDataPath enumDisplayDataPath, bit bEnable);
extern void ScalerDDomainBackgroundSetColor(EnumDisplayDataPath enumDisplayDataPath, BYTE ucRed, BYTE ucGreen, BYTE ucBlue);

