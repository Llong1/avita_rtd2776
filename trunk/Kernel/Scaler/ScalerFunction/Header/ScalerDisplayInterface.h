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
// ID Code      : ScalerDisplayInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
#if(_FRC_SUPPORT == _ON)
extern StructDVCustomizedFreq g_stDVCustomizedFreq;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)

#elif(_PANEL_STYLE == _PANEL_VBO)
extern void ScalerDisplayVboAnalogPhyConrol(bit bEnable);
extern void ScalerDisplayVboHtpdnSetFwControl(bit bEnable);
extern void ScalerDisplayVboForceVideoOutput(bit bEnable);
extern void ScalerDisplayVboPollingHotPlug(WORD usNum);
extern void ScalerDisplayVboHtpdnHandler(void);
extern void ScalerDisplayVboLocknHandler(void);
extern void ScalerDisplayVboPanelSetFastOff(bit bEnable);
extern bit ScalerDisplayVboPanelFastOffCheck(void);
extern void ScalerDisplayVboPanelBacklightReTurnOn(void);

extern void ScalerDisplayVboIntHandler_EXINT0(void);

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
extern BYTE ScalerDisplaySelectDVFMode(void);
#endif

