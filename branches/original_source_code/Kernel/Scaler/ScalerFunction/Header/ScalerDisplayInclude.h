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
// ID Code      : ScalerDisplayInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_VBO)
typedef struct
{
    BYTE b1VboLocknStatus     : 1;
    BYTE b1VboLocknRippedOff  : 1;
    BYTE b1PanelFastOffStatus : 1;
}StructVboInfo;
#endif // #if(_PANEL_STYLE == _PANEL_VBO)

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_VBO)
extern StructVboInfo g_stVboInfo;
#endif

#if(_FRC_SUPPORT == _ON)
extern StructDVCustomizedFreq g_stDVCustomizedFreq;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
extern void ScalerDisplayLvdsTxDataSel(void);
extern void ScalerDisplayLvdsTxPortSwap(void);

#elif(_PANEL_STYLE == _PANEL_VBO)
extern void ScalerDisplayVboMac(bit bOn);
extern void ScalerDisplayVboPhy(bit bOn);
extern void ScalerDisplayVboCdr2AlnLatency(void);
extern void ScalerDisplayVboHtpdnSetFwControl(bit bEnable);

#endif

#if((_FRC_SUPPORT == _ON) || (_OD_SUPPORT == _ON))
extern BYTE ScalerDisplaySelectDVFMode(void);
extern void ScalerDisplaySetDVFreq(void);
#endif

